# LT-3XS664

This is a library for the LT-3XS664(595) display, which has three rows with six, six, and four slots, respectively.

![display_img](assets/display.jpg)

## Usage

```c++
#include <Arduino.h>
#include <Display.h>

Display display(LCD_ENABLE_PIN, LCD_CLK_PIN, LCD_DATA_PIN);

void setup() {
  display.setup();

  display.print("123456", "1.2.3.4.5.6." + "L.O.L. overflow...");
  delay(3000);
  display.printFirstRow("timele");
  display.printSecondRow("s.words.");
  for (int i=0; i<3; ++i) {
    display.printThirdRow(((String)"in " + i));
    delay(1400);
  }
  display.cls(); // clear screen (just fills all slots with space)
  delay(400);
  display.printFirstRow("as5"); delay(400);
  display.printSecondRow("we"); delay(400);
  display.printThirdRow("can"); 
}
```