# Kernel_module_rpi
Interfaz software/hardware entre Raspberry Pi y FPGA Spartan-6 y su aplicación a simulación dirigida por eventos.

El proyecto consiste en desarrollar un driver para linux sobre Raspberry Pi que permita la comunicación
bidireccional, a través de GPIO, con una FPGA. De esta forma podrá integrarse la simulación dirigida por
eventos (formalismo DEVS) mediante el simulador software aDevs, que se ejecuta en la Raspberry Pi, con
una aplicación hardware implantada en una FPGA Spartan-6.
