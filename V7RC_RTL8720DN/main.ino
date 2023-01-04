#include "BLEDevice.h"
#include "AmebaServo.h"


#define UART_SERVICE_UUID      "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

#define STRING_BUF_SIZE 100
#define MaxNumValue      2

typedef struct{
    bool reciveCMDFlag;
    int  ReciveValue;
    int  Pin;
    AmebaServo Servo;

}_rCMD;


BLEService UartService(UART_SERVICE_UUID);
BLECharacteristic Rx(CHARACTERISTIC_UUID_RX);
BLECharacteristic Tx(CHARACTERISTIC_UUID_TX);
BLEAdvertData advdata;
BLEAdvertData scndata;
bool notify = false;
uint8_t Count;

String CMDRefer[5] = {"SS2","SS4","SRT","SR2","SRV"};
uint8_t DefinePin[2] = {3,12};
_rCMD bleReciveData[MaxNumValue];

void readCB (BLECharacteristic* chr, uint8_t connID) {
    printf("Characteristic %s read by connection %d \n", chr->getUUID().str(), connID);
}

void writeCB (BLECharacteristic* chr, uint8_t connID) {
    //printf("Characteristic %s write by connection %d :\n", chr->getUUID().str(), connID);
    if (chr->getDataLen() > 0) {
       ParseCMDString(chr->readString());

        /*
        Serial.print("Received string: ");
        Serial.print(chr->readString());
        Serial.println();   
        */
    }
}

void notifCB (BLECharacteristic* chr, uint8_t connID, uint16_t cccd) {
    if (cccd & GATT_CLIENT_CHAR_CONFIG_NOTIFY) {
        printf("Notifications enabled on Characteristic %s for connection %d \n", chr->getUUID().str(), connID);
        notify = true;
    } else {
        printf("Notifications disabled on Characteristic %s for connection %d \n", chr->getUUID().str(), connID);
        notify = false;
    }
}

void setup()
{
	Serial.begin(115200);

    advdata.addFlags(GAP_ADTYPE_FLAGS_LIMITED | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED);
    advdata.addCompleteName("AMEBA_BLE_DEV");
    scndata.addCompleteServices(BLEUUID(UART_SERVICE_UUID));

    Rx.setWriteNRProperty(true);
    Rx.setWritePermissions(GATT_PERM_WRITE);
    Rx.setWriteCallback(writeCB);
    Rx.setBufferLen(STRING_BUF_SIZE);

    Tx.setReadProperty(true);
    Tx.setReadPermissions(GATT_PERM_READ);
    Tx.setReadCallback(readCB);
    Tx.setNotifyProperty(true);
    Tx.setCCCDCallback(notifCB);
    Tx.setBufferLen(STRING_BUF_SIZE);
    
    UartService.addCharacteristic(Rx);
    UartService.addCharacteristic(Tx);

    BLE.init();
    BLE.configAdvert()->setAdvData(advdata);
    BLE.configAdvert()->setScanRspData(scndata);
    BLE.configServer(1);
    BLE.addService(UartService);

    BLE.beginPeripheral();

    
    for(uint8_t j = 0; j < 2; j++){
        bleReciveData[j].Pin = DefinePin[j];
        bleReciveData[j].Servo.attach(bleReciveData[j].Pin);
    }    

}


void ParseCMDString(String cmd)
{
    int comdLength = cmd.length();

    if(cmd.charAt(comdLength - 1) != '#')
        return;

    if(cmd.indexOf("SRV") > -1 ){

        int x = 3;
        int ValueIndex = 0;

        while(x < comdLength - 1){
            if(x + 3 < comdLength){
                String _NumString = cmd.substring(x,x + 4);
                //Serial.println(_NumString);

                if(ValueIndex < MaxNumValue){
                    if(bleReciveData[ValueIndex].ReciveValue != _NumString.toInt()){
                        bleReciveData[ValueIndex].ReciveValue = _NumString.toInt();
                        bleReciveData[ValueIndex].reciveCMDFlag = true;
                    }
                }

            }

            ValueIndex++;

            x += 4;
            Serial.println();
        }
        
    }
}

void loop()
{

    while(Count < MaxNumValue) {
        
            if(bleReciveData[Count].reciveCMDFlag && bleReciveData[Count].Pin == 3){
                bleReciveData[Count].reciveCMDFlag = false;

                int Angle = map(bleReciveData[Count].ReciveValue,1000,2000,0,180);
                bleReciveData[Count].Servo.write(Angle);
            }
            

            if(bleReciveData[Count].reciveCMDFlag && bleReciveData[Count].Pin == 12){
                bleReciveData[Count].reciveCMDFlag = false;

                int Angle = map(bleReciveData[Count].ReciveValue,1000,2000,0,180);
                bleReciveData[Count].Servo.write(Angle);

            }

        
        Count++;
    }
    Count = 0;
    delay(1);
}
