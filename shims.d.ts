// Auto-generated. Do not edit.
declare namespace _serial2 {

    /**
     * Read a line of text from the serial port and return the buffer when the delimiter is met.
     * @param delimiter text delimiter that separates each text chunk
     */
    //% shim=_serial2::readUntil
    function readUntil(delimiter: string): string;

    /**
     * Read the buffered received data as a string
     */
    //% shim=_serial2::readString
    function readString(): string;

    /**
     * Register an event to be fired when one of the delimiter is matched.
     * @param delimiters the characters to match received characters against.
     */
    //% shim=_serial2::onDataReceived
    function onDataReceived(delimiters: string, body: () => void): void;

    /**
     * Send a piece of text through the serial connection.
     */
    //% shim=_serial2::writeString
    function writeString(text: string): void;

    /**
     * Send a buffer through serial connection
     */
    //% shim=_serial2::writeBuffer
    function writeBuffer(buffer: Buffer): void;

    /**
     * Read multiple characters from the receive buffer.
     * If length is positive, pauses until enough characters are present.
     * @param length default buffer length
     */
    //% shim=_serial2::readBuffer
    function readBuffer(length: int32): Buffer;

    /**
     * Set the serial input and output to use pins instead of the USB connection.
     * @param tx the new transmission pin, eg: SerialPin.P0
     * @param rx the new reception pin, eg: SerialPin.P1
     * @param rate the new baud rate. eg: 115200
     */
    //% shim=_serial2::redirect
    function redirect(tx: SerialPin, rx: SerialPin, rate: BaudRate): void;

    /**
    Set the baud rate of the serial port
     */
    //% shim=_serial2::setBaudRate
    function setBaudRate(rate: BaudRate): void;

    /**
     * Direct the serial input and output to use the USB connection.
     */
    //% shim=_serial2::redirectToUSB
    function redirectToUSB(): void;

    /**
     * Sets the size of the RX buffer in bytes
     * @param size length of the rx buffer in bytes, eg: 32
     */
    //% shim=_serial2::setRxBufferSize
    function setRxBufferSize(size: uint8): void;

    /**
     * Sets the size of the TX buffer in bytes
     * @param size length of the tx buffer in bytes, eg: 32
     */
    //% shim=_serial2::setTxBufferSize
    function setTxBufferSize(size: uint8): void;
}

// Auto-generated. Do not edit. Really.
