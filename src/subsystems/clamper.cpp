#include "main.h"

void clamperInitialize() {

}

void clamperPeriodic() {
    if (driverController.get_digital_new_press(DIGITAL_B)) {
        toggleMogoClamp();
    }
}

void toggleMogoClamp() {
    mogoClamp.toggle();
}