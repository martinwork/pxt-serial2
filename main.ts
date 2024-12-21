
basic.forever(function () {
    serial2.writeString('`');
    basic.pause(1000)
})

control.onEvent(EventBusSource.SERIAL2_DEVICE_ID, EventBusValue.SERIAL2_EVT_DATA_RECEIVED, function () {
    let buf = serial2.readBuffer(0)
    if (buf.length) {
        serial2.writeBuffer(buf)
    }
})

control.onEvent(EventBusSource.SERIAL2_DEVICE_ID, EventBusValue.SERIAL2_EVT_ERROR_FRAMING, function () {
    serial2.writeString('!!frame!!\n')
})

control.onEvent(EventBusSource.SERIAL2_DEVICE_ID, EventBusValue.SERIAL2_EVT_ERROR_BREAK, function () {
    serial2.writeString('!!break!!\n')
})

serial2.setBaudRate(BaudRate.BaudRate2400)
serial2.readString() 
