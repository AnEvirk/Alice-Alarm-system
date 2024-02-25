#include <ESP8266WiFi.h>
#include <AsyncMqttClient.h>
#include <rdm6300.h>
#include <Ticker.h>
extern "C" 
{
    #include "user_interface.h"
}
int _FLPArray59548784[2] = {353048, 14261940 };
bool _FreeLog1_IArr[3];
bool _FreeLog1_Q1_StArr[] = {1, 0, 1};
bool _FreeLog1_Q2_StArr[] = {1, 1, 0};
String mqttServer;
int mqttPort;
String mqttUser;
String mqttPassword;
String mqttClientId;
bool mqttConnected;
std::vector<String> inputTopic;
std::vector<String> inputMessage;
AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
uint16_t pubPacketId;
bool Send_245667527_1;
String Topic_245667527_1;
String Message_245667527_1;
byte QoS_245667527_1;
bool Retain_245667527_1;
bool qosDelivered_245667527_1;
bool rTrig_245667527_1;
uint16_t packetId_245667527_1;
bool Send_245667527_3;
String Topic_245667527_3;
String Message_245667527_3;
byte QoS_245667527_3;
bool Retain_245667527_3;
bool qosDelivered_245667527_3;
bool rTrig_245667527_3;
uint16_t packetId_245667527_3;
bool Unsubscribe_77360925_1;
String Topic_77360925_1;
byte QoS_77360925_1;
bool Received_77360925_1;
String Message_77360925_1;
bool subscribed_77360925_1;
bool rTrig_77360925_1;
bool InHolla;
bool OutHolla;
int AAAAAAA;
#define RDM6300_RX_PIN 13  // can be only 13 - on esp8266 force hardware uart!
#define READ_LED_PIN 16
Rdm6300 rdm6300;
unsigned long timingRDM6300read;
bool Send_245667527_4;
String Topic_245667527_4;
String Message_245667527_4;
byte QoS_245667527_4;
bool Retain_245667527_4;
bool qosDelivered_245667527_4;
bool rTrig_245667527_4;
uint16_t packetId_245667527_4;
bool Send_245667527_2;
String Topic_245667527_2;
String Message_245667527_2;
byte QoS_245667527_2;
bool Retain_245667527_2;
bool qosDelivered_245667527_2;
bool rTrig_245667527_2;
uint16_t packetId_245667527_2;
bool ESPControllerWifiClient_HRD = 0;
bool ESPControllerWifiClient_status = 1;
bool ESPControllerWifiClient_isDHCP = 1;
bool ESPControllerWifiClient_IsNeedReconect = 0;
bool ESPControllerWifiClient_workStatus = 1;
char ESPControllerWifiClient_SSID[40] = "408";
char ESPControllerWifiClient_password[40] = "408408408spb";
IPAddress ESPControllerWifiClient_ip(0, 0, 0, 0);
IPAddress  ESPControllerWifiClient_dns (0, 0, 0, 1);
IPAddress  ESPControllerWifiClient_gateway (0, 0, 0, 1);
IPAddress ESPControllerWifiClient_subnet (255, 255, 255, 0);
uint8_t ESPControllerWifiClient_mac[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
String _gtv1;
bool _gtv2 = 0;
bool _gtv3 = 1;
bool _trgrt2 = 0;
bool _trgrt2I = 0;
bool _tim3I = 0;
bool _tim3O = 0;
unsigned long _tim3P = 0UL;
bool _gen1I = 0;
bool _gen1O = 0;
unsigned long _gen1P = 0UL;
bool _tim7I = 0;
bool _tim7O = 0;
unsigned long _tim7P = 0UL;
bool _tim5I = 0;
bool _tim5O = 0;
unsigned long _tim5P = 0UL;
bool _bounseInputD0S = 0;
bool _bounseInputD0O = 0;
unsigned long _bounseInputD0P = 0UL;
bool _changeNumber1_Out = 0;
int _changeNumber1_OLV;
bool _tim4I = 0;
bool _tim4O = 0;
unsigned long _tim4P = 0UL;
bool _trgrt1 = 0;
bool _trgrt1I = 0;
bool _gen3I = 0;
bool _gen3O = 0;
unsigned long _gen3P = 0UL;
bool _FreeLog1_Q1 = 0;
bool _FreeLog1_Q2 = 0;
bool _tim2I = 0;
bool _tim2O = 0;
unsigned long _tim2P = 0UL;
bool _tim1I = 0;
bool _tim1O = 0;
unsigned long _tim1P = 0UL;
bool _gen2I = 0;
bool _gen2O = 0;
unsigned long _gen2P = 0UL;
bool _tim6I = 0;
bool _tim6O = 0;
unsigned long _tim6P = 0UL;
bool _pzs1OES = 0;
bool _gen4I = 0;
bool _gen4O = 0;
unsigned long _gen4P = 0UL;
bool _trgs1 = 0;
int _tempVariable_int;
void setup()
{
    pinMode(0, INPUT);
    pinMode(5, OUTPUT);
    digitalWrite(5, 0);
    WiFi.mode(WIFI_STA);
    _esp8266WifiModuleClientReconnect();
    _bounseInputD0O =  digitalRead(0);
    wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
    wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
    mqttClient.onMessage(onMqttMessage);
    mqttClient.onConnect(onMqttConnect);
    mqttClient.onDisconnect(onMqttDisconnect);
    mqttClient.onPublish(onMqttPublish);
    mqttClient.setKeepAlive(15);
    mqttClient.setCleanSession(0);
    pinMode(READ_LED_PIN, OUTPUT);
    digitalWrite(READ_LED_PIN, LOW);
    rdm6300.begin(RDM6300_RX_PIN);
}
void loop()
{
    if(ESPControllerWifiClient_IsNeedReconect) 
    {
        _esp8266WifiModuleClientReconnect();
        ESPControllerWifiClient_IsNeedReconect = 0;
    }
    ESPControllerWifiClient_status = WiFi.status() == WL_CONNECTED;
    if (ESPControllerWifiClient_status) 
    {
         if (! ESPControllerWifiClient_HRD) 
        {
            ESPControllerWifiClient_ip =  WiFi.localIP();
            ESPControllerWifiClient_subnet =  WiFi.subnetMask();
            ESPControllerWifiClient_gateway =  WiFi.gatewayIP();
            ESPControllerWifiClient_dns =  WiFi.dnsIP();
            WiFi.macAddress(ESPControllerWifiClient_mac);
            ESPControllerWifiClient_HRD = 1;
        }
    }
     else 
    {
        ESPControllerWifiClient_HRD = 0;
    }
    bool  _bounceInputTmpD0 =  (digitalRead (0));
    if (_bounseInputD0S)
    {
        if (millis() >= (_bounseInputD0P + 40))
        {
            _bounseInputD0O= _bounceInputTmpD0;
            _bounseInputD0S=0;
        }
    }
    else
    {
        if (_bounceInputTmpD0 != _bounseInputD0O)
        {
            _bounseInputD0S=1;
            _bounseInputD0P = millis();
        }
    }
    //Плата:1
    mqttServer = String("m6.wqtt.ru");
    mqttPort = 11954;
    mqttUser = String("u_FX3M2T");
    mqttPassword = String("aDR7R4tC");
    mqttClientId = String("SKUD");
    Send_245667527_1 = 0;
    Topic_245667527_1 = String("python/mqtt");
    Message_245667527_1 = String("33245");
    QoS_245667527_1 = 0;
    Retain_245667527_1 = 0;
    pub(Send_245667527_1, Topic_245667527_1, Message_245667527_1, QoS_245667527_1, Retain_245667527_1, qosDelivered_245667527_1, packetId_245667527_1, rTrig_245667527_1);
    //Плата:2
//Наименование:Активный режим
    if (_bounseInputD0O) 
    {
         if (_trgrt1I) 
        {
             _trgrt1 = 0;
        }
         else 
        {
            _trgrt1 = 1;
            _trgrt1I = 1;
        }
    }
     else 
    {
        _trgrt1 = 0;
        _trgrt1I = 0;
    }
    ;
    InHolla = _trgrt1;
    if (millis() > 5000)
    {
        OutHolla = InHolla;
    }
    else
    {
        OutHolla = 0;
    }
    if(((OutHolla) && (!(_gtv3)))) 
    {
        _tim1O = 1;
        _tim1I = 1;
    }
     else 
    {
         if(_tim1I) 
        {
            _tim1I = 0;
            _tim1P = millis();
        }
         else 
        {
             if (_tim1O) 
            {
                if (_isTimer(_tim1P, 10000)) _tim1O = 0;
            }
        }
    }
    if (_tim1O)
    {
         if (_tim3I) 
        {
             if (_isTimer(_tim3P, 9900)) 
            {
                _tim3O = 1;
            }
        }
         else 
        {
            _tim3I =1;
            _tim3P = millis();
        }
    }
     else 
    {
        _tim3O = 0;
        _tim3I = 0;
    }
    if (((_tim1O) && (((String("closed")).equalsIgnoreCase(_gtv1))))) 
    {
         if (! _gen3I) 
        {
            _gen3I = 1;
            _gen3O = 1;
            _gen3P = millis();
        }
    }
     else 
    {
        _gen3I = 0 ;
        _gen3O= 0;
    }
    if (_gen3I) 
    {
          if (_isTimer (_gen3P , 700)) 
        {
             _gen3P = millis();
            _gen3O = ! _gen3O;
        }
    }
    digitalWrite(5, _gen3O);
    Send_245667527_3 = ((_tim3O) && (((String("closed")).equalsIgnoreCase(_gtv1))));
    Topic_245667527_3 = String("python/mqtt");
    Message_245667527_3 = String("33245");
    QoS_245667527_3 = 2;
    Retain_245667527_3 = 0;
    pub(Send_245667527_3, Topic_245667527_3, Message_245667527_3, QoS_245667527_3, Retain_245667527_3, qosDelivered_245667527_3, packetId_245667527_3, rTrig_245667527_3);
    Unsubscribe_77360925_1 = 0;
    Topic_77360925_1 = String("ProtectionActive");
    QoS_77360925_1 = 2;
    sub(Topic_77360925_1, Message_77360925_1, QoS_77360925_1, Received_77360925_1, subscribed_77360925_1, Unsubscribe_77360925_1, rTrig_77360925_1);
    _gtv1 = Message_77360925_1;
    //Плата:3
//Наименование:RFID
     if (millis() - timingRDM6300read > 100)
    {
        timingRDM6300read = millis();
        if (rdm6300.get_tag_id()) 
        {
            AAAAAAA = rdm6300.get_tag_id();
            digitalWrite(READ_LED_PIN, rdm6300.get_tag_id());
        }
        if (!rdm6300.get_tag_id()) 
        {
            AAAAAAA = 00000000;
        }
    }
    if (((_findElementFromIntegerArray(_FLPArray59548784, 2, (AAAAAAA))) > -1)) 
    {
         if (_trgrt2I) 
        {
             _trgrt2 = 0;
        }
         else 
        {
            _trgrt2 = 1;
            _trgrt2I = 1;
        }
    }
     else 
    {
        _trgrt2 = 0;
        _trgrt2I = 0;
    }
    ;
    if(_trgrt2) 
    {
        _tim5O = 1;
        _tim5I = 1;
    }
     else 
    {
         if(_tim5I) 
        {
            _tim5I = 0;
            _tim5P = millis();
        }
         else 
        {
             if (_tim5O) 
            {
                if (_isTimer(_tim5P, 2000)) _tim5O = 0;
            }
        }
    }
    if (_tim5O) 
    {
        if (! _gen2I)
        {
            _gen2I = 1;
            _gen2O = 1;
            _gen2P = millis();
        }
    }
     else 
    {
        _gen2I = 0 ;
        _gen2O= 0;
    }
     if (_gen2I &&  _gen2O)   _gen2O = !(_isTimer(_gen2P , 700));
    digitalWrite(5, _gen2O);
    _FreeLog1_IArr[0] = _trgrt2;
    _FreeLog1_IArr[1] = ((String("closed")).equalsIgnoreCase(_gtv1));
    _FreeLog1_IArr[2] = ((String("opened")).equalsIgnoreCase(_gtv1));
    _FreeLog1_Q1 = _checkFreeLogicBlockOutput(_FreeLog1_IArr, 3, _FreeLog1_Q1_StArr, 3);
    _FreeLog1_Q2 = _checkFreeLogicBlockOutput(_FreeLog1_IArr, 3, _FreeLog1_Q2_StArr, 3);
    Send_245667527_2 = _FreeLog1_Q2;
    Topic_245667527_2 = String("ProtectionActive");
    Message_245667527_2 = String("opened");
    QoS_245667527_2 = 2;
    Retain_245667527_2 = 0;
    pub(Send_245667527_2, Topic_245667527_2, Message_245667527_2, QoS_245667527_2, Retain_245667527_2, qosDelivered_245667527_2, packetId_245667527_2, rTrig_245667527_2);
    if(_FreeLog1_Q1) _trgs1 = 1;
    if(_gtv2) _trgs1 = 0;
    if(_trgs1) 
    {
        _tim2O = 1;
        _tim2I = 1;
    }
     else 
    {
         if(_tim2I) 
        {
            _tim2I = 0;
            _tim2P = millis();
        }
         else 
        {
             if (_tim2O) 
            {
                if (_isTimer(_tim2P, 10000)) _tim2O = 0;
            }
        }
    }
    _gtv3 = _tim2O;
    if (_tim2O) 
    {
         if (! _gen1I) 
        {
            _gen1I = 1;
            _gen1O = 1;
            _gen1P = millis();
        }
    }
     else 
    {
        _gen1I = 0 ;
        _gen1O= 0;
    }
    if (_gen1I) 
    {
          if (_isTimer (_gen1P , 700)) 
        {
             _gen1P = millis();
            _gen1O = ! _gen1O;
        }
    }
    if(_trgrt2) 
    {
        _tim7O = 1;
        _tim7I = 1;
    }
     else 
    {
         if(_tim7I) 
        {
            _tim7I = 0;
            _tim7P = millis();
        }
         else 
        {
             if (_tim7O) 
            {
                if (_isTimer(_tim7P, 3000)) _tim7O = 0;
            }
        }
    }
    if (_changeNumber1_Out) 
    {
        _changeNumber1_Out = 0;
    }
     else 
    {
        if (!(_tim7O)) 
        {
            _tempVariable_int = AAAAAAA;
            if (_tempVariable_int != _changeNumber1_OLV) 
            {
                _changeNumber1_OLV = _tempVariable_int;
                _changeNumber1_Out = 1;
            }
        }
    }
    if(((_changeNumber1_Out) && (!(_trgrt2)))) 
    {
        _tim6O = 1;
        _tim6I = 1;
    }
     else 
    {
         if(_tim6I) 
        {
            _tim6I = 0;
            _tim6P = millis();
        }
         else 
        {
             if (_tim6O) 
            {
                if (_isTimer(_tim6P, 110)) _tim6O = 0;
            }
        }
    }
    if (_tim6O) 
    {
        if (! _gen4I)
        {
            _gen4I = 1;
            _gen4O = 1;
            _gen4P = millis();
        }
    }
     else 
    {
        _gen4I = 0 ;
        _gen4O= 0;
    }
     if (_gen4I &&  _gen4O)   _gen4O = !(_isTimer(_gen4P , 100));
    if(((_gen4O) || (_gen1O)))
    {
        if((!_pzs1OES))
        {
             tone(4, 8000);
            _pzs1OES =1;
        }
    }
     else 
    {
        if(_pzs1OES)
        {
            noTone(4);
            _pzs1OES =0;
        }
    }
    _gtv2 = _tim2O;
    if (_tim2O)
    {
         if (_tim4I) 
        {
             if (_isTimer(_tim4P, 9900)) 
            {
                _tim4O = 1;
            }
        }
         else 
        {
            _tim4I =1;
            _tim4P = millis();
        }
    }
     else 
    {
        _tim4O = 0;
        _tim4I = 0;
    }
    Send_245667527_4 = _tim4O;
    Topic_245667527_4 = String("ProtectionActive");
    Message_245667527_4 = String("closed");
    QoS_245667527_4 = 2;
    Retain_245667527_4 = 0;
    pub(Send_245667527_4, Topic_245667527_4, Message_245667527_4, QoS_245667527_4, Retain_245667527_4, qosDelivered_245667527_4, packetId_245667527_4, rTrig_245667527_4);
}
bool _isTimer(unsigned long startTime, unsigned long period)
{
    unsigned long currentTime;
    currentTime = millis();
    if (currentTime>= startTime) 
    {
        return (currentTime>=(startTime + period));
    }
     else 
    {
        return (currentTime >=(4294967295-startTime+period));
    }
}
int _findElementFromIntegerArray(int array[], int arraySize, int value)
{
    for (int i = 0; i < arraySize; i = i + 1) 
    {
        if(array[i] == value)
        {
            return i;
        }
    }
    return -1;
}
bool _checkFreeLogicBlockOutput(bool inArray[], int inArraySize, bool stArray[], int stArraySize)
{
    int inIndex = 0;
    bool result = 1;
    for (int i = 0; i < stArraySize; i = i + 1)
    {
        if (!(inArray[inIndex] == stArray[i])) 
        {
             result = 0;
        }
        inIndex ++;
        if (inIndex == inArraySize)
        {
            if (result) 
            {
                 return 1;
            }
             else 
            {
                result = 1;
            }
            inIndex = 0;
        }
    }
    return 0;
}
void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
    char msg[len + 1];
    for (size_t i = 0; i < len; i++) 
    {
        	msg[i] = payload[i];
    }
    msg[len] = '\0';
    inputTopic.push_back(String(topic));
    inputMessage.push_back(String(msg));
}
void onWifiConnect(const WiFiEventStationModeGotIP& event)
{
    connectToMqtt();
}
void onWifiDisconnect(const WiFiEventStationModeDisconnected& event)
{
    mqttReconnectTimer.detach();
}
void connectToMqtt()
{
    if ("default" == "default") 
    {
        	mqttClient.setWill(mqttClientId.c_str(), 1, 0, "0");
    }
     else 
    {
        	mqttClient.setWill("default", 1, 0, "0");
    }
    mqttClient.setClientId(mqttClientId.c_str());
    mqttClient.setServer(mqttServer.c_str(), mqttPort);
    mqttClient.setCredentials(mqttUser.c_str(), mqttPassword.c_str());
    mqttClient.connect();
}
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
    mqttConnected = false;
    	
    if (WiFi.isConnected()) 
    {
            mqttReconnectTimer.once(5, connectToMqtt);
    }
}
void onMqttConnect(bool sessionPresent)
{
    mqttConnected = true;
    if ("default" == "default") 
    {
        	mqttClient.publish(mqttClientId.c_str(), 1, 0, "1");
    }
     else 
    {
        	mqttClient.publish("default", 1, 0, "1");
    }
}
void onMqttPublish(uint16_t packetId)
{
    pubPacketId = packetId;
}
void sub(const String &topic, String &message, const byte &qos, bool &received, bool &subscribed, const bool &unsubscribe, bool &rTrig)
{
    received = false;
    if (unsubscribe) 
    {
        	if (!rTrig) 
        {
            		uint16_t packetId = mqttClient.unsubscribe(topic.c_str());
            		if (packetId > 0) 
            {
                			rTrig = true;
                			subscribed = false;
                			for (uint8_t i = 0; i < inputTopic.size(); i++) 
                {
                    				if (inputTopic[i] == topic) 
                    {
                        					inputTopic.erase(inputTopic.begin() + i);
                        					inputMessage.erase(inputMessage.begin() + i);
                        					if (inputTopic.empty()) 
                        {
                            						inputTopic.shrink_to_fit();
                            						inputMessage.shrink_to_fit();
                            					
                        }
                        				
                    }
                    			
                }
                		
            }
            	
        }
    }
     else 
    {
        	rTrig = false;
        	for (uint8_t i = 0; i < inputTopic.size(); i++) 
        {
            		if (inputTopic[i] == topic) 
            {
                			received = true;
                			message = inputMessage[i];
                			inputTopic.erase(inputTopic.begin() + i);
                			inputMessage.erase(inputMessage.begin() + i);
                			if (inputTopic.empty()) 
                {
                    				inputTopic.shrink_to_fit();
                    				inputMessage.shrink_to_fit();
                    			
                }
                			break;
                		
            }
            	
        }
        	if (mqttClient.connected()) 
        {
            		if (!subscribed) 
            {
                			uint16_t packetId = mqttClient.subscribe(topic.c_str(), qos);
                			if (packetId > 0) 
                {
                    				subscribed = true;
                    			
                }
                		
            }
            	
        }
         else 
        {
            		subscribed = false;
            	
        }
    }
}
void pub(const bool &send, const String &topic, const String &message, const byte &qos, const bool &retain, bool &qosDelivered, uint16_t &packetId, bool &rTrig)
{
    if (send) 
    {
        	if (!rTrig) 
        {
            		packetId = mqttClient.publish(topic.c_str(), qos, retain, message.c_str());
            		if (packetId > 0) 
            {
                			rTrig = true;
                		
            }
            	
        }
    }
     else 
    {
        	rTrig = false;
        	qosDelivered = false;
    }
    if (packetId > 1 && packetId == pubPacketId) 
    {
        	qosDelivered = true;
        	packetId = 0;
    }
}
int hexStrToInt(String instring)
{
    byte len = instring.length();
    if  (len == 0) return 0;
    int result = 0;
    for (byte i = 0; i < 8; i++)    // только первые 8 цыфар влезуть в uint32
    {
        char ch = instring[i];
        if (ch == 0) break;
        result <<= 4;
        if (isdigit(ch))
        result = result | (ch - '0');
        else result = result | (ch - 'A' + 10);
    }
    return result;
}
void _esp8266WifiModuleClientReconnect()
{
    if(_checkMacAddres(ESPControllerWifiClient_mac)) 
    {
          wifi_set_macaddr(0, const_cast<uint8*>(ESPControllerWifiClient_mac));
    }
    if(ESPControllerWifiClient_isDHCP) 
    {
         WiFi.config(0U, 0U, 0U, 0U, 0U);
    }
     else 
    {
        WiFi.config(ESPControllerWifiClient_ip, ESPControllerWifiClient_gateway, ESPControllerWifiClient_subnet, ESPControllerWifiClient_dns , ESPControllerWifiClient_dns);
    }
    WiFi.begin(ESPControllerWifiClient_SSID, ESPControllerWifiClient_password);
}
bool _checkMacAddres(byte array[])
{
    bool result = 0;
    for (byte i = 0; i < 6; i++)
    {
        if (array[i] == 255) 
        {
            return 0;
        }
        if (array[i] > 0) 
        {
            result = 1;
        }
    }
    return result;
}
void _parseMacAddressString(String value, byte array[])
{
    int index;
    byte buffer[6] = {255, 255, 255, 255, 255, 255};
    byte raz = 0;
    String tempString;
    while ((value.length() > 0) && (raz <= 6)) 
    {
        index = value.indexOf(":");
        if (index == -1) 
        {
            tempString = value;
            value = "";
        }
         else 
        {
            tempString = value.substring(0, index);
            value = value.substring(index + 1);
        }
        buffer[raz] = byte(hexStrToInt(tempString));
        raz++;
    }
    if (_checkMacAddres(buffer))
    {
        for (byte i = 0; i < 6; i++)
        {
            array[i] = buffer[i];
        }
    }
}
bool _compareMacAddreses(byte array1[], byte array2[])
{
    for (byte i = 0; i < 6; i++)
    {
        if (array1[i] != array2[i]) 
        {
            return 0;
        }
    }
    return 1;
}
bool _compareMacAddresWithString(byte array[], String value)
{
    byte buffer[6] = {255, 255, 255, 255, 255, 255};
    _parseMacAddressString(value,  buffer);
    return _compareMacAddreses(array, buffer);
}
bool _checkMacAddresString(String value)
{
    byte buffer[6] = {255, 255, 255, 255, 255, 255};
    _parseMacAddressString(value,  buffer);
    return _checkMacAddres(buffer);
}
String _macAddresToString(byte array[])
{
    String result = "";
    String  temp ="";
    for (byte i = 0; i < 6; i++)
    {
        temp=String(array[i],HEX);
        if (temp.length()  < 2) 
        {
            temp = String("0") + temp;
        }
        result = result + temp;
        if (i < 5) 
        {
               result = result + String(":");
        }
    }
    result.toUpperCase();
    return result;
}
