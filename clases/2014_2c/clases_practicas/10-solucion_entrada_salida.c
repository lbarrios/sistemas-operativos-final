int driver_write(int * data) {
    int bits = *data;
    for (int i = 0; i < 3; i++){
        OUT(SP_DATA, bits & 0x1); // Recordar que 1 no es 0x1
        OUT(SP_CTRL, SP_SEND);
        while(IN(SP_STATUS) != SP_NOT_READ)
            sleep(1);
        bits = bits >> 1;
    }
    return IO_OK;
}

int driver_read(int * data) {
    int bits = 0;
    for (int i = 0; i < 3; i++){
        bits = bits << 1;
        OUT(SP_CTRL, SP_RECEIVE);
        while(IN(SP_STATUS) != SP_NOT_READ)
            sleep(1);
        int val = IN(SP_DATA);
        bits = bits | (val & 0x1);
    }
    *data = bits;
    return IO_OK;
}

//========================================
// SOLUCION CON IRQ

mutex access = 1;
mutex transfer = 1;
sem ready = 0;
int * data_in_transfer;

int driver_init() {
    if(request_irq(3, next) == IRQ_ERROR)
        return IO_ERROR;
    return IO_OK;
}

int driver_remove() {
    free_irq(3);
    return IO_OK;
}

int driver_open() {
    access.wait();
}

int driver_close() {
    access.signal();
}

int driver_write(int * data) {
    transfer.wait();
    reading = 0;
    data_in_transfer = data;
    OUT(SP_DATA, *data_in_transfer & 0x1); // Recordar que 1 no es 0x1
    OUT(SP_CTRL, SP_SEND);
    ready.wait();
    transfer.signal()
    return IO_OK;
}

int driver_read(int * data) {
    transfer.wait();
    reading = 1;
    data_in_transfer = data;
    OUT(SP_CTRL, SP_RECEIVE);
    ready.wait();
    *data = *data_in_transfer;
    transfer.signal()
    return IO_OK;
}

void next() {
    irq++;
    if (reading){
        //LLego una lectura
        int val = IN(SP_DATA); //Leo lo que llego
        *data_in_transfer = (*data_in_transfer<<0x1) | (val & 0x1); //lo acomodo en data
        if(irq != 3) // sino termine
            OUT(SP_CTRL, SP_RECEIVE);
    } else if(irq != 3) { // Solo vuelvo a enviar si faltan envios.
        *data_in_transfer = *data_in_transfer >> 1;
        OUT(SP_DATA, *data_in_transfer & 0x1); // Recordar que 1 no es 0x1
        OUT(SP_CTRL, SP_SEND);
    }
    if(irq == 2){
        //termine de leer o enviar
        irq = 0;
        ready.signal();
    }
}
