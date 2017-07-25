/**
 * Copyright (c) 2016, Jack Mo (mobangjack@foxmail.com).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "dbuf.h"

void DBuf_Init(DBuf_t* dbuf)
{
	Rcf_Init(&dbuf->rcf);
	Hcf_Init(&dbuf->hcf);
}

void DBuf_Proc(DBuf_t* dbuf, const DBus_t* dbus)
{
	Rcf_Proc(&dbuf->rcf, &dbus->rcp);
	Hcf_Proc(&dbuf->hcf, &dbus->hcp);
}

