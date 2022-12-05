#include "hw_driver.h"
#include "stc15f2k60s2.h"
#include "types.h"

int8 cur_x;  // Column
int8 cur_y;  // Row
int8 cur_v;

void MySleep() {
  DelayMs(100);
	while (WasButtonPressed(kOkBtn) > 0) {
  	cur_v = 1;
	}
	while (WasButtonPressed(kRstBtn) > 0) {
  	cur_v = 0;
	}
  while (WasButtonPressed(kDownBtn)) {  // Down
		if (cur_y == 15) {
			// Nothingness.
		} else {
      SetPixelValue(cur_y, cur_x, cur_v);
      cur_y = cur_y + 1;
			cur_v = GetPixelValue(cur_y, cur_x);
      if (IsButtonDown(kOkBtn) > 0) {
        cur_v = 1;
      }
      if (IsButtonDown(kRstBtn) > 0) {
        cur_v = 0;
      }
		}
  }
	while (WasButtonPressed(kUpBtn) > 0) {
		if (cur_y == 0) {
			// Nothing again.
		} else {
      SetPixelValue(cur_y, cur_x, cur_v);
      cur_y = cur_y - 1;
			cur_v = GetPixelValue(cur_y, cur_x);
      if (IsButtonDown(kOkBtn) > 0) {
        cur_v = 1;
      }
      if (IsButtonDown(kRstBtn) > 0) {
        cur_v = 0;
      }
		}
  }
	while (WasButtonPressed(kRightBtn) > 0) {
		if (cur_x == 7) {
			// Do nothing.
		} else {
      SetPixelValue(cur_y, cur_x, cur_v);
      cur_x = cur_x + 1;
			cur_v = GetPixelValue(cur_y, cur_x);
      if (IsButtonDown(kOkBtn) > 0) {
        cur_v = 1;
      }
      if (IsButtonDown(kRstBtn) > 0) {
        cur_v = 0;
      }
		}
  }
	while (WasButtonPressed(kLeftBtn) > 0) {
		if (cur_x == 0) {
			// Nothing!
		} else {
      SetPixelValue(cur_y, cur_x, cur_v);
			cur_x = cur_x - 1;
			cur_v = GetPixelValue(cur_y, cur_x);
      if (IsButtonDown(kOkBtn) > 0) {
        cur_v = 1;
      }
      if (IsButtonDown(kRstBtn) > 0) {
        cur_v = 0;
      }
		}
  }
}

void main(void) {
  InitHw();

  cur_x = 2;
  cur_y = 2;
	cur_v = 0;

  while (1) {
    SetPixel(cur_y, cur_x);
		MySleep();
		MySleep();
    ClearPixel(cur_y, cur_x);
		MySleep();
		MySleep();
  }
}

// For some reason if the interrupt method is declared in hw_driver.c
// it doesn't work. Need to declare it here and invoke the other one.
void OnTickInt() __interrupt(1) {
  OnTick();
}
