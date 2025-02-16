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

#![no_std]
#![cfg_attr(target_vendor = "teaclave", feature(rustc_private))]
#![feature(slice_ptr_get)]
#![allow(static_mut_refs)]
#![allow(clippy::missing_safety_doc)]

#[macro_use]
extern crate alloc as alloc_crate;

extern crate sgx_sync;
extern crate sgx_trts;
#[macro_use]
extern crate sgx_types;

mod rsrvmm;

pub mod alloc;
#[cfg(feature = "capi")]
pub mod capi;
pub mod map;
