/**
 * HopeIDE Debug Adapter
 * Implements Debug Adapter Protocol (DAP) for VS Code debugging
 */

import {
    DebugSession,
    InitializedEvent,
    TerminatedEvent,
    StoppedEvent,
    BreakpointEvent,
    OutputEvent,
    Thread,
    StackFrame,
    Scope,
    Source,
    Handles,
    Breakpoint
} from '@vscode/debugadapter';
import { DebugProtocol } from '@vscode/debugprotocol';
import { GDBBackend } from '../services/gdbBackend';
import { OpenOCDService } from '../services/openocdService';
import * as path from 'path';

export class HopeIDEDebugSession extends DebugSession {
    private gdb: GDBBackend;
    private openocd: OpenOCDService;
    private variableHandles = new Handles<string>();
    private breakpoints: Map<string, DebugProtocol.Breakpoint[]> = new Map();

    constructor() {
        super();
        this.gdb = new GDBBackend();
        this.openocd = new OpenOCDService();

        // Setup GDB event listeners
        this.gdb.on('async', this.handleGDBAsync.bind(this));
        this.gdb.on('closed', () => {
            this.sendEvent(new TerminatedEvent());
        });

        this.openocd.on('output', (data: string) => {
            this.sendEvent(new OutputEvent(data, 'console'));
        });
    }

    protected initializeRequest(
        response: DebugProtocol.InitializeResponse,
        args: DebugProtocol.InitializeRequestArguments
    ): void {
        response.body = {
            supportsConfigurationDoneRequest: true,
            supportsEvaluateForHovers: true,
            supportsStepBack: false,
            supportsSetVariable: true,
            supportsRestartFrame: false,
            supportsGotoTargetsRequest: false,
            supportsStepInTargetsRequest: false,
            supportsCompletionsRequest: false,
            supportsModulesRequest: false,
            supportsRestartRequest: false,
            supportsExceptionOptions: false,
            supportsValueFormattingOptions: true,
            supportsExceptionInfoRequest: false,
            supportTerminateDebuggee: true,
            supportsDelayedStackTraceLoading: false,
            supportsLoadedSourcesRequest: false,
            supportsLogPoints: false,
            supportsTerminateThreadsRequest: false,
            supportsSetExpression: false,
            supportsTerminateRequest: true,
            supportsDataBreakpoints: false,
            supportsReadMemoryRequest: true,
            supportsDisassembleRequest: false
        };

        this.sendResponse(response);
    }

    protected async launchRequest(
        response: DebugProtocol.LaunchResponse,
        args: any
    ): Promise<void> {
        try {
            this.sendEvent(new OutputEvent('🚀 Starting HopeIDE debugger...\n', 'console'));

            // Start OpenOCD with retry
            this.sendEvent(new OutputEvent('⚡ Starting OpenOCD...\n', 'console'));
            await this.openocd.startWithRetry(this.getTargetConfig(args.device), 3);
            this.sendEvent(new OutputEvent('✅ OpenOCD started\n', 'console'));

            // Start GDB
            this.sendEvent(new OutputEvent('🔧 Starting GDB...\n', 'console'));
            await this.gdb.start(args.program);
            this.sendEvent(new OutputEvent('✅ GDB started\n', 'console'));

            // Connect to OpenOCD
            this.sendEvent(new OutputEvent('🔗 Connecting to target...\n', 'console'));
            await this.gdb.connect('localhost', 3333);
            this.sendEvent(new OutputEvent('✅ Connected to target\n', 'console'));

            this.sendEvent(new InitializedEvent());
            this.sendResponse(response);

        } catch (error: any) {
            this.sendEvent(new OutputEvent(`❌ Debug launch failed: ${error.message}\n`, 'stderr'));
            this.sendErrorResponse(response, 1, error.message);
        }
    }

    protected async setBreakPointsRequest(
        response: DebugProtocol.SetBreakpointsResponse,
        args: DebugProtocol.SetBreakpointsArguments
    ): Promise<void> {
        const path = args.source.path!;
        const clientLines = args.lines || [];

        const breakpoints: DebugProtocol.Breakpoint[] = [];

        for (const line of clientLines) {
            try {
                const bpNum = await this.gdb.setBreakpoint(path, line);
                breakpoints.push({
                    verified: true,
                    line: line,
                    id: bpNum
                });
            } catch (error) {
                breakpoints.push({
                    verified: false,
                    line: line
                });
            }
        }

        this.breakpoints.set(path, breakpoints);
        response.body = { breakpoints };
        this.sendResponse(response);
    }

    protected threadsRequest(response: DebugProtocol.ThreadsResponse): void {
        response.body = {
            threads: [new Thread(1, 'Main Thread')]
        };
        this.sendResponse(response);
    }

    protected async stackTraceRequest(
        response: DebugProtocol.StackTraceResponse,
        args: DebugProtocol.StackTraceArguments
    ): Promise<void> {
        const frames: StackFrame[] = [
            new StackFrame(1, 'main', new Source('main.c', '/path/to/main.c'), 1, 0)
        ];

        response.body = {
            stackFrames: frames,
            totalFrames: 1
        };
        this.sendResponse(response);
    }

    protected scopesRequest(
        response: DebugProtocol.ScopesResponse,
        args: DebugProtocol.ScopesArguments
    ): void {
        response.body = {
            scopes: [
                new Scope('Locals', this.variableHandles.create('locals'), false),
                new Scope('Registers', this.variableHandles.create('registers'), false)
            ]
        };
        this.sendResponse(response);
    }

    protected async variablesRequest(
        response: DebugProtocol.VariablesResponse,
        args: DebugProtocol.VariablesArguments
    ): Promise<void> {
        const handle = this.variableHandles.get(args.variablesReference);
        const variables: DebugProtocol.Variable[] = [];

        if (handle === 'locals') {
            // TODO: Get locals from GDB
            variables.push({
                name: 'counter',
                value: '0',
                variablesReference: 0
            });
        } else if (handle === 'registers') {
            // TODO: Get registers from GDB
            variables.push({
                name: 'r0',
                value: '0x00000000',
                variablesReference: 0
            });
        }

        response.body = { variables };
        this.sendResponse(response);
    }

    protected async continueRequest(
        response: DebugProtocol.ContinueResponse,
        args: DebugProtocol.ContinueArguments
    ): Promise<void> {
        await this.gdb.continue();
        this.sendResponse(response);
    }

    protected async nextRequest(
        response: DebugProtocol.NextResponse,
        args: DebugProtocol.NextArguments
    ): Promise<void> {
        await this.gdb.stepOver();
        this.sendResponse(response);
    }

    protected async stepInRequest(
        response: DebugProtocol.StepInResponse,
        args: DebugProtocol.StepInArguments
    ): Promise<void> {
        await this.gdb.stepInto();
        this.sendResponse(response);
    }

    protected async pauseRequest(
        response: DebugProtocol.PauseResponse,
        args: DebugProtocol.PauseArguments
    ): Promise<void> {
        await this.gdb.pause();
        this.sendResponse(response);
    }

    protected async disconnectRequest(
        response: DebugProtocol.DisconnectResponse,
        args: DebugProtocol.DisconnectArguments
    ): Promise<void> {
        await this.gdb.quit();
        await this.openocd.stop();
        this.sendResponse(response);
    }

    private handleGDBAsync(event: string, data: any) {
        if (event === 'stopped') {
            this.sendEvent(new StoppedEvent('breakpoint', 1));
        } else if (event === 'running') {
            // Target is running
        }
    }

    private getTargetConfig(device: string): string {
        // Map device to OpenOCD target config
        if (device.startsWith('STM32F0')) return 'stm32f0x';
        if (device.startsWith('STM32F1')) return 'stm32f1x';
        if (device.startsWith('STM32F4')) return 'stm32f4x';
        if (device.startsWith('STM32F7')) return 'stm32f7x';
        if (device.startsWith('STM32H7')) return 'stm32h7x';
        if (device.startsWith('STM32L4')) return 'stm32l4x';
        return 'stm32f4x'; // Default
    }
}
