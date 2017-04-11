# Automated DoorBell
A simple arduino C++ scheme to automate a gate's opening on doorbell ring. Definitely not safe for home use ;-)

Currently relying on a Diode Bridge Rectifier to get the doorbell's AC input and detect a ring, and a Grove Relay to close the door opening circuit, mounted in parallel to the doorbell's original button.

There is a voluntary random delay (5000 to 30000 ms) between ring detection and gate opening signal.

By default, the system will output the highest input voltage detected from the doorbell, in order to help identifying the peaks related to a ring.

## Debug

Sending the "o" command through Serial will immediately send the gate opening signal, with no delay.

Sending the "m" command through Serial will start a "monitoring session", displaying the highest input voltage detected from the doorbell. This can be stopped using the "e" command.

Sending the "d" command through Serial will start debugging mode, displaying a more verbose output, along with all the input readings from the doorbell.
