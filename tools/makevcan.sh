#!/bin/bash
#
# DFM

echo Please run as superuser~

modprobe can
modprobe can_raw
modprobe can_bcm
modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
ip link show vcan0
