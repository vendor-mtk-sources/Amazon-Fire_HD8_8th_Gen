################################################################################
#
#  build_kernel_config.sh
#
#  Copyright (c) 2016-2022 Amazon.com, Inc. or its affiliates. All Rights Reserved.
#
################################################################################

KERNEL_SUBPATH="kernel/mediatek/mt8163/4.9"
DEFCONFIG_NAME="karnak_defconfig"
TARGET_ARCH="arm64"
TOOLCHAIN_PREFIX="aarch64-linux-gnu-"

# Expected image files are seperated with ":"
KERNEL_IMAGES="arch/arm64/boot/Image:arch/arm64/boot/Image.gz"

################################################################################
# NOTE: You must fill in the following with the path to a copy of
#       aarch64-linux-gnu-6.3.1 compiler.
################################################################################
CROSS_COMPILER_PATH=""
