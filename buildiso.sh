#!/bin/bash

make

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp bin/evergreen isodir/boot/evergreen

cat > isodir/boot/grub/grub.cfg << EOF
menuentry "evergreen" {
        multiboot /boot/evergreen
}
EOF

grub-mkrescue -o evergreen.iso isodir
