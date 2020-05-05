#ifndef _CCS811_H_
#define _CCS811_H_

#include <M5Stack.h>
#define CCS811_SLAVE_ADDRESS (0x5B)

class CCS811{
    public:
        CCS811();
        ~CCS811();
        bool begin(CommUtil *_i2c);
        bool init();
        bool isConnected();
        bool resetSenser();
        bool checkUpdate();
        void updateSenser();
        uint16_t getEco2(); // 400〜8,192 ppm
        uint16_t getTvoc(); // 0〜1,187 ppb
    private:
        CommUtil *i2c;
        uint16_t eco2;
        uint16_t tvoc;
};

#endif