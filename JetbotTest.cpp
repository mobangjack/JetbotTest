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
#include "uart.h"
#include <iostream>

#define BUF_LEN 256

using namespace std;

void publishBotMsg(const BotMsg_t* botMsg)
{
  
  cout << "bot------ " << \
          "id:" << botMsg->frame_id << "," << \
          "px:" << botMsg->cbus.cp.x << "," << \
          "py:" << botMsg->cbus.cp.y << "," << \
          "pz:" << botMsg->cbus.cp.z << "," << \
          "vx:" << botMsg->cbus.cv.x << "," << \
          "vy:" << botMsg->cbus.cv.y << "," << \
          "vz:" << botMsg->cbus.cv.z << endl;
}

void publishUwbMsg(const UwbMsg_t* uwbMsg)
{
  cout << "uwb------ " << \
          "id:" << uwbMsg->frame_id << "," << \
          "flag:" << uwbMsg->flag << "," << \
          "x:" << uwbMsg->x << "," << \
          "y:" << uwbMsg->y << "," << \
          "z:" << uwbMsg->z << "," << \
          "w:" << uwbMsg->w << endl;
}

void publishZGyroMsg(const ZGyroMsg_t* zgyroMsg)
{
  cout << "zgyro------ " << \
          "id:" << zgyroMsg->frame_id << "," << \
          "angle:" << zgyroMsg->angle << "," << \
          "rate:" << zgyroMsg->rate << endl;
}

DBus_t dbus;
void publishVDBusMsg(const VDBusMsg_t* vdbusMsg)
{
  DBus_Dec(&dbus, vdbusMsg->data);
  cout << "vdbus------ " << \
          "id:" << vdbusMsg->frame_id << "," << \
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

#define TEST_CNT 1e6

int main(int argc, char **argv)
{
  uint32_t test_cnt = 0;
  
  int uart_fd = -1;
  
  FIFO_t rx_fifo;
  uint8_t rx_buf[2][BUF_LEN];

  FIFO_Init(&rx_fifo, rx_buf[0], BUF_LEN);

  UwbMsg_t uwbMsg;
  BotMsg_t botMsg;
  ZGyroMsg_t zgyroMsg;
  VDBusMsg_t vdbusMsg;

  std::string serial_port = "/dev/ttyUSB0";
  int serial_baudrate = 115200;
  int spin_rate = 100;

  int ret = uart_open(&uart_fd, serial_port.c_str(), serial_baudrate, UART_OFLAG_RD);
  if (ret < 0) {
    fprintf(stderr, "Error, cannot bind to the specified serial port %s.\n"
            , serial_port.c_str());
    return -1;
  }

  while (++test_cnt < TEST_CNT)
  {

    // Get fifo free space
    int len = FIFO_GetFree(&rx_fifo);
    
    // If fifo free space insufficient, pop one element out
    if (len < 1) {
      uint8_t b;
      len = FIFO_Pop(&rx_fifo, &b, 1);
    }
    
    // Read input stream according to the fifo free space left
    len = uart_read(uart_fd, rx_buf[1], len);
    
    // Check if there is any new stream
    if (len > 0) {
      // Push new stream into fifo
      FIFO_Push(&rx_fifo, rx_buf[1], len);
    }

    // Check if any message received
    
    if (Msg_Pop(&rx_fifo, rx_buf[1], &MSG_HEAD_OF(BOT), &botMsg)) {
      publishBotMsg(&botMsg);
    }

    if (Msg_Pop(&rx_fifo, rx_buf[1], &MSG_HEAD_OF(UWB), &uwbMsg)) {
      publishUwbMsg(&uwbMsg);
    }
    
    if (Msg_Pop(&rx_fifo, rx_buf[1], &MSG_HEAD_OF(ZGYRO), &zgyroMsg)) {
      publishZGyroMsg(&zgyroMsg);
    }

    if (Msg_Pop(&rx_fifo, rx_buf[1], &MSG_HEAD_OF(VDBUS), &vdbusMsg)) {
      publishVDBusMsg(&vdbusMsg);
    }
    
  }

  // Done
  uart_close(uart_fd);

  return 0;
}



