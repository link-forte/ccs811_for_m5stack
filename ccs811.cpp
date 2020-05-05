#include "ccs811.h"

CCS811::CCS811(){
    i2c = nullptr;
    eco2 = 0;
    tvoc = 0;
}

CCS811::~CCS811(){
}

bool CCS811::begin(CommUtil *_i2c){
    i2c = _i2c;

    if(isConnected())
        if(init())
            return true;

return false;
}

bool CCS811::init(){
    if(!i2c->writeByte(CCS811_SLAVE_ADDRESS, 0x01, 0x10))
        return false;
    delay(10);

    if(!i2c->writeCommand(CCS811_SLAVE_ADDRESS, 0xF4))
        return false;
    delay(10);

return true;
}

bool CCS811::isConnected() {
    uint8_t res = 0;
    if(i2c->readByte(CCS811_SLAVE_ADDRESS, 0x20, &res))
        if(res == 0x81)
            return true;

return false;
}

bool CCS811::resetSenser(){
    uint8_t rx[4] = {0x11, 0xE5, 0x72, 0x8A};
    if(i2c->writeBytes(CCS811_SLAVE_ADDRESS, 0xFF, rx, 4))
            if(init())
                return true;

return false;
}

bool CCS811::checkUpdate(){
    uint8_t res;
    if(i2c->readByte(CCS811_SLAVE_ADDRESS, 0x00, &res))
        return (res & 1 << 3);

return false;
}

void CCS811::updateSenser(){
    uint8_t res[8] = {0};
    if(i2c->readBytes(CCS811_SLAVE_ADDRESS, 0x02, 8, res)){
        eco2 = ((uint16_t)res[0] << 8) | res[1];
        tvoc = ((uint16_t)res[2] << 8) | res[3];
    }
}

uint16_t CCS811::getEco2(){

return eco2;
}

uint16_t CCS811::getTvoc(){

return tvoc;
}