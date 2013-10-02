#!/bin/bash
#
# Temporarily hits Linux in the head making it think that it's a Superpenguin (aka. has a cape, aka. has a CAN interface) so we can test our program. 
# Warning: do not run while under influence of alcohol. Who knows what booze can do to penguins. 
#
sudo modprobe can
sudo modprobe can_raw
sudo modprobe can_bcm
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
ip link show vcan0
