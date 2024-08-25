// A serial-driven adb device emulator
// 2024 Ed Paradis

void setup() {
  // init the serial port that will be used upstream

  // init the ADB interface

}

byte pending; // bit mask of what commands are pending
#define MOUSE 1>>0
#define KEYBOARD 1>>1

void loop() {
  // check for a new host command
  recv_host_cmd();

  // ADB is host controlled. get the latest command
  cmd = recv_adb_cmd( /* ?? */ );

  // device 3 by default is the mouse
  if( adb_cmd_address(cmd) == 3 && adb_cmd_register(cmd) == 0xC ) {
    if( is_pending(MOUSE)) {
      send_adb_mouse_data();
      clear_pending(MOUSE);
    }
  }

  // device 2 by default is the keyboard
  if( adb_cmd_address(cmd) == 2 ) {
    switch( adb_cmd_register(cmd) ) {
      case 0xC:
        if( is_pending(KEYBOARD)) {
          send_adb_keyboard_data();
          clear_pending(KEYBOARD)
        }
        break;
      case 0xD:
        break;
      case 0xE:
        send_adb_keyboard_extended_data()
        break;
      case 0xF:
        break;
      default:
        // error
        break;
    }
  }

}
