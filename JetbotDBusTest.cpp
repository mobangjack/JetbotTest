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

#include "asp.h"
#include <iostream>

#define BUF_LEN 256

using namespace std;

DBus_t dbus;
uint8_t buf[DBUS_FRAME_LEN];
void test()
{
  DBus_Init(&dbus);
  dbus.rcp.sw[0] = SW_MD;
  dbus.rcp.sw[1] = SW_UP;
  
  cout << "dbus------before codec " << \
          "ch1:" << dbus.rcp.ch[0] << "," << \
          "ch2:" << dbus.rcp.ch[1] << "," << \
          "ch3:" << dbus.rcp.ch[2] << "," << \
          "ch4:" << dbus.rcp.ch[3] << "," << \
          "sw1:" << (int)dbus.rcp.sw[0] << "," << \
          "sw2:" << (int)dbus.rcp.sw[1] << "," << \
          "msx:" << (int)dbus.hcp.mouse.x << "," << \
          "msy:" << (int)dbus.hcp.mouse.y << "," << \
          "msz:" << (int)dbus.hcp.mouse.z << "," << \
          "key:" << dbus.hcp.key.val << endl;
  DBus_Enc(&dbus, buf);
  DBus_Dec(&dbus, buf);
  cout << "dbus------after codec " << \
          "ch1:" << dbus.rcp.ch[0] << "," << \
          "ch2:" << dbus.rcp.ch[1] << "," << \
          "ch3:" << dbus.rcp.ch[2] << "," << \
          "ch4:" << dbus.rcp.ch[3] << "," << \
          "sw1:" << (int)dbus.rcp.sw[0] << "," << \
          "sw2:" << (int)dbus.rcp.sw[1] << "," << \
          "msx:" << (int)dbus.hcp.mouse.x << "," << \
          "msy:" << (int)dbus.hcp.mouse.y << "," << \
          "msz:" << (int)dbus.hcp.mouse.z << "," << \
          "key:" << dbus.hcp.key.val << endl;
}

#define TEST_CNT 1e2

int main(int argc, char **argv)
{
  uint32_t test_cnt = 0;
  
  while (++test_cnt < TEST_CNT)
  {
    test();
  }

  return 0;
}



