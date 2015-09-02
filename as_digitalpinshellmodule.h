// -----------------------------------------------------------------------
// DigitalPinShell module
//
// Manipulate the digital pins, and save the config to EEPROM.
// -----------------------------------------------------------------------

#ifndef __AS_DIGITALPINSHELLMODULE_H__
#define __AS_DIGITALPINSHELLMODULE_H__

#include "as_shellmodule.h"

class DigitalPinShell : public ShellModule
{
public:
    static const uint32_t MODULE_ID = 0x4450534d; // 'DPSM' - used to identify the module config block in EEPROM.
    static const uint8_t  MAX_PINS  = 64;

    //! Specifies where in EEPROM the defaults are stored.
    const uint32_t configBase;
    
    void setup();
    
    void help() override;
    void run(String rawCommand) override;

    void saveDefaults() override;
    // void loadDefaults() override;

private:
    struct
    {
        uint32_t id;     // MODULE_ID needs to be stored there, or the config block SHOULD NOT BE USED.
        uint32_t crc;    // Currently using a 16-bit CRC, can shrink this field for other uses if needed.

        uint64_t io;     // INPUT = 0, OUTPUT = 1
        uint64_t pullup; // INPUT_PULLUP means set this = 1, when necessary.
        uint64_t value;  // HIGH or LOW.
    } config;

    void configPinMode (const uint8_t pin, const int mode);
    void configPinValue(const uint8_t pin, const int value);
public:
    DigitalPinShell(const uint32_t configBase);
};

#endif  /* __AS_DIGITALPINSHELLMODULE_H__ */
