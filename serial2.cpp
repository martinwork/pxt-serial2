#include "pxt.h"
#include "./NRF52Serial2.h"

#define MICROBIT_SERIAL_READ_BUFFER_LENGTH 64

// make sure USB_TX and USB_RX don't overlap with other pin ids
// also, 1001,1002 need to be kept in sync with getPin() function
enum SerialPin
{
};

enum BaudRate
{
};

// TODO:
#if 0
enum EventBusSource
{
    //% blockIdentity="control.eventSourceId"
    SERIAL2_DEVICE_ID = IMQOPEN_NRF52SERIAL2_DEFAULT_DEVICE_ID,
};

enum EventBusValue
{
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_DELIM_MATCH = IMQOPEN_NRF52SERIAL2_EVT_DELIM_MATCH,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_HEAD_MATCH = IMQOPEN_NRF52SERIAL2_EVT_HEAD_MATCH,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_RX_FULL = IMQOPEN_NRF52SERIAL2_EVT_RX_FULL,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_DATA_RECEIVED = IMQOPEN_NRF52SERIAL2_EVT_DATA_RECEIVED,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_ERROR_OVERRUN = IMQOPEN_NRF52SERIAL2_EVT_ERROR_OVERRUN,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_ERROR_PARITY = IMQOPEN_NRF52SERIAL2_EVT_ERROR_PARITY,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_ERROR_FRAMING = IMQOPEN_NRF52SERIAL2_EVT_ERROR_FRAMING,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_ERROR_BREAK = IMQOPEN_NRF52SERIAL2_EVT_ERROR_BREAK,
};
#else
enum EventBusSource
{
    //% blockIdentity="control.eventSourceId"
    SERIAL2_DEVICE_ID = 70,
};

enum EventBusValue
{
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_DELIM_MATCH = 1,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_HEAD_MATCH = 2,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_RX_FULL = 3,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_DATA_RECEIVED = 4,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_ERROR_OVERRUN = 10,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_ERROR_PARITY = 11,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_ERROR_FRAMING = 12,
    //% blockIdentity="control.eventValueId"
    SERIAL2_EVT_ERROR_BREAK = 13,
};
#endif

namespace serial2
{

    imqopen::NRF52Serial2 serial2(uBit.io.P13, uBit.io.P14);
    // bool is_redirected;

    // note that at least one // followed by % is needed per declaration!

    /*
     * Read a line of text from the serial port and return the buffer when the delimiter is met.
     * @param delimiter text delimiter that separates each text chunk
     */
    //%
    String readUntil(String delimiter)
    {
        return PSTR(serial2.readUntil(MSTR(delimiter)));
    }

    /*
     * Read the buffered received data as a string
     */
    //%
    String readString()
    {
        int n = serial2.getRxBufferSize();
        if (n == 0)
            return mkString("", 0);
        return PSTR(serial2.read(n, MicroBitSerialMode::ASYNC));
    }

    /*
     * Register an event to be fired when one of the delimiter is matched.
     * @param delimiters the characters to match received characters against.
     */
    //%
    void onDataReceived(String delimiters, Action body)
    {
        serial2.eventOn(MSTR(delimiters));
        registerWithDal(SERIAL2_DEVICE_ID, MICROBIT_SERIAL_EVT_DELIM_MATCH, body);
        // lazy initialization of serial buffers
        serial2.read(MicroBitSerialMode::ASYNC);
    }

    /*
     * Send a piece of text through the serial connection.
     */
    //%
    void writeString(String text)
    {
        if (!text)
            return;

        serial2.send(MSTR(text));
    }

    /*
     * Send a buffer through serial connection
     */
    //%
    void writeBuffer(Buffer buffer)
    {
        if (!buffer)
            return;

        serial2.send(buffer->data, buffer->length);
    }

    /*
     * Read multiple characters from the receive buffer.
     * If length is positive, pauses until enough characters are present.
     * @param length default buffer length
     */
    //%
    Buffer readBuffer(int length)
    {
        auto mode = SYNC_SLEEP;
        if (length <= 0)
        {
            length = serial2.getRxBufferSize();
            mode = ASYNC;
        }

        auto buf = mkBuffer(NULL, length);
        auto res = buf;
        registerGCObj(buf); // make sure buffer is pinned, while we wait for data
        int read = serial2.read(buf->data, buf->length, mode);
        if (read != length)
        {
            res = mkBuffer(buf->data, read);
        }
        unregisterGCObj(buf);

        return res;
    }

    /*
     * Set the serial input and output to use pins instead of the USB connection.
     * @param tx the new transmission pin, eg: SerialPin.P0
     * @param rx the new reception pin, eg: SerialPin.P1
     * @param rate the new baud rate. eg: 115200
     */
    //%
    void redirect(SerialPin tx, SerialPin rx, BaudRate rate)
    {

        if (getPin(tx) && getPin(rx))
        {
            serial2.redirect(*getPin(tx), *getPin(rx));
            // is_redirected = 1;
        }
        serial2.setBaud(rate);
    }

    /*
    Set the baud rate of the serial port
    */
    //%
    void setBaudRate(BaudRate rate)
    {
        serial2.setBaud(rate);
    }

    /*
     * Direct the serial input and output to use the USB connection.
     */
    //%
    void redirectToUSB()
    {
        // is_redirected = false;
        serial2.redirect(uBit.io.usbTx, uBit.io.usbRx);
        serial2.setBaud(115200);
    }

    /*
     * Sets the size of the RX buffer in bytes
     * @param size length of the rx buffer in bytes, eg: 32
     */
    //%
    void setRxBufferSize(uint8_t size)
    {
        serial2.setRxBufferSize(size);
    }

    /*
     * Sets the size of the TX buffer in bytes
     * @param size length of the tx buffer in bytes, eg: 32
     */
    //%
    void setTxBufferSize(uint8_t size)
    {
        serial2.setTxBufferSize(size);
    }

} // namespace serial2
