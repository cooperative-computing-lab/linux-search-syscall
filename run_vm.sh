#!/bin/bash

sudo virsh destroy search-vm
sudo virsh undefine search-vm
sudo virt-install --name search-vm --ram 2000 --network network:default --nographics --boot kernel=/afs/nd.edu/user37/ccl/work/bkokoszk/linux-search/linux/arch/x86/boot/bzImage,initrd=/boot/initramfs-3.4.0-SEARCH-SYSCALL.img,kernel_args='root=UUID=e5d9dc39-1eec-4098-8037-0d938a8e1867 ro console=tty0 console=ttyS0\,115200 rdshell' --init=/sbin/init --noautoconsole --disk path=/var/tmp/root.img,format=raw,bus=virtio,device=disk,cache=none --vcpus=2
sudo virsh console search-vm
