# my2440
my2440 project
1. 使用openocd烧写S3C2440的nandflash
	a) 准备工作：sudo apt-get install openocd
	b) openocd 需要配置自己的openocd.cfg，配置文件可以放在当前执行openocd的目录，也可以是用参数-f指定。我目前的openocd.cfg配置如下：
	source [find interface/jlink.cfg]
	source [find board/mini2440.cfg]
	c) openocd的配置脚本目录在/usr/share/openocd/scripts, 其中
	修改了jlink.cfg的配置：adapter_khz 250
	修改了mini2440.cfg的配置：
	    #nand device s3c2440 0
	    set _NANDNAME $_CHIPNAME.nand
	    nand device $_NANDNAME s3c2440 $_TARGETNAME
	以便能够烧写nandflash.
	d) 烧写步骤：
		1. 打开终端 openocd -f /YOUR_PATH/openocd.cfg, 提示能够正确识别s3c2440
		2. 打开另一终端： telnet localhost 4444

		出现如下信息：
		tgni@B460:~$ telnet localhost 4444
		Trying 127.0.0.1...
		Connected to localhost.
		Escape character is '^]'.
		Open On-Chip Debugger
		> 
		执行 halt

		> halt
		target state: halted
		target halted in ARM state due to debug-request, current mode: Supervisor
		cpsr: 0x20000093 pc: 0xc0731dec
		MMU: enabled, D-Cache: enabled, I-Cache: enabled
		> 

		nand probe 0
		nand erase 0 0 0x60000 #大小必须是0x20000（blocksize）的整数倍
		nand write 0 u-boot.bin 0

2. 利用buildroot制作交叉编译工具链。
	a) 使用版本buildroot-2014.02
	b) buildroot的编译
		make mini2440_defconfig
		make menuconfig
		make
	生成的toolchain在output/host目录，值得一提的是，buildroot可以编译整个mini2440的uboot,kernel和fs。这里我们不去尝试了。因为默认编译的uboot网络有bug，一直checksum bad...
	我生成的toolchain版本是arm-linu-gcc v4.7.3.
	buildroot编译过程中遇到的错误都是简单的问题，大部分是因为系统太新，头文件找不到或者结构定义找不到，修复一下就没问题了。
	生成的toolchain放在/opt/toolchian/目录下，并且export PATH=/opt/toolchain/usr/bin:$PATH
	如果是tcsh则使用set path = ($PATH /opt/toolchain/usr/bin)

3. uboot 编译
	已经移植好的uboot-2010.06编译生成uboot.bin

4. kernel的编译
	进入kernel目录，
	cp my2440_config .config
	make menuconfig
	注意：我这里选择的是 ramfs, 所以进入
		General setup  --->
			 [*] Initial RAM filesystem and RAM disk (initramfs/initrd) support
			 (/home/tgni/my2440/root-2.6.30.4) Initramfs source file(s)   
	选择正确的rootfs目录，其他默认即可。
	编译过程可能遇到错误，细心排查即可。
	kernel生成zImage没办法使用uboot直接加载，需要通过uboot生成的mkimage工具来制作uImage。
	具体命令如下：
	mkimage -n 'tekkaman' -A arm -O linux -T kernel -C none -a 0x30008000 -e 0x30008040 -d zImage zImage.img
	
	mkimage 选项定义：
	参数说明：
		-A 指定CPU的体系结构，可用值有：alpha、arm 、x86、ia64、mips、mips64、ppc 、s390、sh、sparc 、sparc64、m68k等
		-O 指定操作系统类型，可用值有：openbsd、netbsd、freebsd、4_4bsd、linux、svr4、esix、solaris、irix、sco、dell、ncr、lynxos、vxworks、psos、qnx、u-boot、rtems、artos
		-T 指定映象类型，可用值有：standalone、kernel、ramdisk、multi、firmware、script、filesystem
		-C 指定映象压缩方式，可用值有：
		none 不压缩(一般使用这个，因为zImage是已经被bzip2压缩过的自解压内核)
		gzip 用gzip的压缩方式
		bzip2 用bzip2的压缩方式
		-a 指定映象在内存中的加载地址，映象下载到内存中时，要按照用mkimage制作映象时，这个参数所指定的地址值来下载
		-e 指定映象运行的入口点地址，这个地址就是-a参数指定的值加上0x40（因为前面有个mkimage添加的0x40个字节的头）
		-n 指定映象名
		-d 指定制作映象的源文件

5. rootfs的注意点：
	因为rootfs的制作是我之前已经制作好的。根文件系统的制作参考blog 

	Tekkaman Ninja
	http://blog.chinaunix.net/uid/20543672.html

	但是一些使用mknod命令制作的文件会失效，小心看tar包的提示。
	tar: Exiting with failure status due to previous errors

	root-2.6.30.4/dev/null
	tar: root-2.6.30.4/dev/null: Cannot mknod: Operation not permitted
	root-2.6.30.4/dev/console
	tar: root-2.6.30.4/dev/console: Cannot mknod: Operation not permitted

	因此：进入 dev目录：
	mknod -m 600 console c 5 1;mknod -m 666 null c 1 3; (need root)

6. uboot 烧写总结：
	a) ubuntu tftpd 服务器搭建
		sudo apt-get install tftpd-hpa
		sudo vim /etc/default/tftpd-hpa3
		输入如下：
			# /etc/default/tftpd-hpa
			TFTP_USERNAME="tftp"
			TFTP_DIRECTORY="/home/tgni/tftpboot"
			TFTP_ADDRESS="[::]:69"
			#TFTP_OPTIONS="--secure"
			TFTP_OPTIONS="-l -c -s"
		sudo service tftpd-hpa start
	b) 将u-boot.bin, zImage.img 放入/home/tgni/tftpboot, 这里tftpboot的权限是777
	c) 烧写bootloader
		tftp 0x30008000 u-boot.bin
		nand erase 0 0x60000
		nand write 0x30008000 0 0x60000
		其中前面256K是boot， 128K是bootconfig
	d) 烧写kernel
		tftpboot 0x30008000 zImage.img
		nand erase 0x60000 0x500000
		nand write 0x30008000 0x60000 0x500000
	e) 因为是ramfs，所以不需要额外烧写rootfs分区了。
	f) 设置bootloader自动加载内核
	   bootloader环境变量
		u-boot2010.06@Daniel # printenv
		bootdelay=3
		baudrate=115200
		ethaddr=08:00:3e:26:0a:5b
		ethact=dm9000
		filesize=4E6590
		fileaddr=30008000
		netmask=255.255.255.0
		ipaddr=192.168.2.105
		serverip=192.168.2.15
		bootcmd=nand read 0x30008000 0x60000 0x500000;bootm 0x30008000
		stdin=serial
		stdout=serial
		stderr=serial
	   命令为：
	   setenv bootcmd 'nand read 0x30008000 0x60000 0x500000;bootm 0x30008000'
	   saveenv
