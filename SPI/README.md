# Periodic Bidirectional Communication over SPI

This design deals with such a use case:

- Communication between two ends (microcontrollers, or DSPs) over SPI;
- The communication is periodic;
- The communication should be as efficient as possible;
- The SPI slave should be able to request a transfer.

The last point listed above may be not so easy to implement, since SPI slave has no control over the timing, and only SPI master can initiate a transfer. To make SPI slave be able to request a transfer, a mechanism need to be added, in addition to the `standard` SPI 4 wires.

In this design, the mechanism is a signal, called XREQ (transfer request). It is used by SPI slave to inform SPI master: please start SPI clocking (and since the SPI transfer). This signal can be implemented as an interrupt raised by SPI slave, and handled by SPI master.

Since SPI slave has no control over the timing, every transfer should be started by the mechanism described above, in case of that the SPI master accidently started a transfer while the SPI slave is not ready for SPI communication yet.

To make it simple, we make the data amount to be transfered equal for both sides. If one side has less data, it just pads dummy data.

With the mechanism above, the periodic communication can be described as:

1. A timer (or just follow a periodic task) runs at the SPI slave side, to trigger the periodic communication.
2. When a period is triggered, and SPI slave is ready to communicate, it asserts the XREQ signal.
3. SPI master handles the XREQ signal, and prepares for SPI communication.
4. When SPI master is ready, it starts SPI clocking, and an SPI transfer starts.
5. When the transfer ends, both sides have all their data transfered (note the data amount is equal).
6. Repeat from step 1.

For better performance, a DMA channel can be used to transfer data between main RAM and SPI data register.
