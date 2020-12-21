# project-stop-and-wait-arq-crc32-simulation-c-

Flow Control and Error Control Techniques in the Data Link Layer Protocols

Introduction:
Stop-and-wait ARQ, also referred to as alternating bit protocol, is a method in telecommunications to send information between two connected devices. It ensures that information is not lost due to dropped packets and that packets are received in the correct order. It is the simplest automatic repeat-request (ARQ) mechanism. A stop-and-wait ARQ sender sends one frame at a time; it is a special case of the general sliding window protocol with transmit and receive window sizes equal to one in both cases. After sending each frame, the sender doesn't send any further frames until it receives an acknowledgement (ACK) signal. After receiving a valid frame, the receiver sends an ACK.
If the ACK does not reach the sender before a certain time, known as the timeout, the sender sends the same frame again. The timeout countdown is reset after each frame transmission. The above behavior is a basic example of Stop-and-Wait. However, real-life implementations vary to address certain issues of design.
We are also using CRC-32 method to check if the received data is the same as the sender tried to send. Where data size will be long and the Divisor will be 32 bit long Binary code.
Typically the transmitter adds a redundancy check number to the end of each frame. The receiver uses the redundancy check number to check for possible damage. If the receiver sees that the frame is good, it sends an ACK. If the receiver sees that the frame is damaged, the receiver discards it and does not send an ACK—pretending that the frame was completely lost, not merely damaged. 
One problem is when the ACK sent by the receiver is damaged or lost. In this case, the sender doesn't receive the ACK, times out, and sends the frame again. Now the receiver has two copies of the same frame, and doesn't know if the second one is a duplicate frame or the next frame of the sequence carrying identical DATA. 
Another problem is when the transmission medium has such a long latency that the sender's timeout runs out before the frame reaches the receiver. In this case the sender resends the same packet. Eventually the receiver gets two copies of the same frame, and sends an ACK for each one. The sender, waiting for a single ACK, receives two ACKs, which may cause problems if it assumes that the second ACK is for the next frame in the sequence. 
To avoid those issues, we are implementing the Stop and wait ARQ along with CRC-32 checksum.

 
Protocol Description
1.	In stop-and-wait ARQ sender sends one frame at a time. 
2.	It waits for ACK then sends another frame, or resend if there’s any fault sending.
3.	After receiving a valid frame, the receiver sends an ACK. 
4.	In receiver will data will be checked using (CRC-32) if the data is valid or not. After checking, receiver sends ACK if the data is OK.
5.	If the ACK does not reach the sender before a certain time, time error will be shown and the frame will be resend.
6.	Finally receiver will receive the data.
