// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License..

//! # Trusted Runtime System

#![no_std]
#![cfg_attr(target_vendor = "teaclave", feature(rustc_private))]
#![allow(internal_features)]
#![feature(allocator_api)]
#![feature(const_trait_impl)]
#![feature(core_intrinsics)]
#![feature(extract_if)]
#![feature(maybe_uninit_uninit_array)]
#![feature(min_specialization)]
#![feature(negative_impls)]
#![feature(never_type)]
#![feature(ptr_internals)]
#![feature(thread_local)]
#![allow(clippy::missing_safety_doc)]
#![allow(dead_code)]
#![allow(non_camel_case_types)]
#![allow(static_mut_refs)]

#[cfg(all(feature = "sim", feature = "hyper"))]
compile_error!("feature \"sim\" and feature \"hyper\" cannot be enabled at the same time");

extern crate alloc;

#[macro_use]
extern crate sgx_types;
#[cfg(not(feature = "use_sgx_sdk"))]
extern crate sgx_crypto_sys;
#[cfg(not(feature = "use_sgx_sdk"))]
extern crate sgx_tlibc_sys;

#[macro_use]
mod arch;
#[cfg(not(feature = "use_sgx_sdk"))]
mod asm;
#[cfg(feature = "use_sgx_sdk")]
mod asm_sgx_sdk;
mod call;
#[macro_use]
mod elf;
mod enclave;

mod inst;
#[cfg(not(feature = "hyper"))]
mod pkru;
mod stackchk;
mod version;
mod xsave;

#[cfg(not(feature = "use_sgx_sdk"))]
pub mod capi;
#[cfg(feature = "use_sgx_sdk")]
pub mod capi_sgx_sdk;

#[cfg(not(any(feature = "sim", feature = "hyper")))]
pub mod aexnotify;
pub mod edmm;
pub mod error;
#[macro_use]
pub mod feature;
pub mod fence;
pub mod macros;
pub mod rand;
pub mod se;
pub mod sync;
pub mod tcs;
#[cfg(feature = "thread")]
pub mod thread;
pub mod trts;
pub mod veh;
