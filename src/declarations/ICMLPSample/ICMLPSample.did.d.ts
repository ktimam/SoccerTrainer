import type { Principal } from '@dfinity/principal';
import type { ActorMethod } from '@dfinity/agent';
import type { IDL } from '@dfinity/candid';

export interface GreetingRecord { 'greeting' : string }
export type GreetingRecordResult = { 'Ok' : GreetingRecord } |
  { 'Err' : StatusCode };
export type StatusCode = number;
export interface _SERVICE { 'train' : ActorMethod<[], string> }
export declare const idlFactory: IDL.InterfaceFactory;
export declare const init: (args: { IDL: typeof IDL }) => IDL.Type[];
