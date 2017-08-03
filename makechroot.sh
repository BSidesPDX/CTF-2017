#!/bin/bash

#usage: makechroot.sh <challenge.sh> <challengeName>
#make a basic chroot capable of running bash

#<challenge.sh> should copy the challenge files to /docker/* (a chroot)
#including required libs if any

#<challengeName> will be the container tgz name

EXTRASCRIPT=`pwd`/$1
TAG=$2

BASE=`pwd`/docker
LIBS='ld-linux-*so* libc*so* librt*so  libtinfo*so* libselinux*so*
     libnss_files*so* libnss_dns*so* libresolv*so* libdl*so* ld-*so
     libpthread*so libgcc*so* libz*so* libpcre*so*'
USRLIBS='libstdc++.so*'
LIB64S='ld-linux*'
BINS='sh bash dash ls grep cat'
SBINS='ldconfig ldconfig.real'

LIBDIR=/lib/x86_64-linux-gnu
USRLIBDIR=/usr/lib/x86_64-linux-gnu
LIB64DIR=/lib64

mkdir -p $BASE/$LIBDIR
mkdir -p $BASE/$LIB64DIR
mkdir -p $BASE/sbin
mkdir -p $BASE/bin
mkdir -p $BASE/$USRLIBDIR
mkdir -p $BASE/etc

for LIB in $LIBS; do
    cp -av $LIBDIR/$LIB $BASE/$LIBDIR/	
done

for ULIB in $USRLIBS; do
    cp -av $USRLIBDIR/$ULIB $BASE/$USRLIBDIR/
done

for LIB in $LIB64S; do
    cp -av $LIB64DIR/$LIB $BASE/$LIB64DIR/
done

for BIN in $BINS; do
    cp -av /bin/$BIN $BASE/bin/
done

for SBIN in $SBINS; do
    cp -av /sbin/$SBIN $BASE/sbin/
done

echo "127.0.0.1 localhost" > $BASE/etc/hosts
echo "$LIBDIR" > $BASE/etc/ld.so.conf
echo "$USRLIBDIR" >> $BASE/etc/ld.so.conf

cat <<EOF > $BASE/etc/nsswitch.conf
passwd: compat
group: compat
shadow: compat
hosts: files dns
networks: files
protocols: files
services: files
ethers: files
rpc: files
netgroup: nis
EOF


BASE=$BASE $EXTRASCRIPT

#generate the ld.so.cache
ldconfig -r $BASE

cd $BASE

tar czfp ../$TAG.tgz .
