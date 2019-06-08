if ! ./buildiso.sh; then
  echo "Building ISO failed"
  exit 1
fi

qemu-system-i386 evergreen.iso
