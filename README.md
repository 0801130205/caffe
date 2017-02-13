# DSSD : Deconvolutional Single Shot Detector

[![License](https://img.shields.io/badge/license-BSD-blue.svg)](LICENSE)

By [Cheng-Yang Fu*](http://www.cs.unc.edu/~cyfu/), [Wei Liu*](http://www.cs.unc.edu/~wliu/), Ananth Ranga, Ambrish Tyagi, [Alexander C. Berg](http://acberg.com).

*=Equal Contribution

### Introduction

[arXiv paper](https://arxiv.org/abs/1701.06659) 

### Citing DSSD

Please cite DSSD in your publications if it helps your research:

    @inproceedings{Fu2016dssd,
      title = {{DSSD}: Deconvolutional Single Shot Detector},
      author = {Fu, Cheng-Yang and Liu, Wei and Ranga, Ananth and Tyagi, Ambrish and Berg, Alexander C.},
      booktitle = {arXiv preprint arXiv:1701.06659},
    }


### Contents
1. [Installation](#installation)
2. [Preparation](#preparation)
3. [Train/Eval](#traineval)

### Installation
1. Download the code from github. We call this directory as `$CAFFE_ROOT` later.

	```Shell
	git clone https://github.com/chengyangfu/caffe.git
	cd $CAFFE_ROOT
	git checkout dssd
	```
	
2. Build the code. Please follow [Caffe instruction](http://caffe.berkeleyvision.org/installation.html) to install all necessary packages and build it.

	```Shell
  	# Modify Makefile.config according to your Caffe installation.
  	cp Makefile.config.example Makefile.config
  	make -j8
  	# Make sure to include $CAFFE_ROOT/python to your PYTHONPATH.
  	make py
  	make test -j8
  	# (Optional)
  	make runtest -j
  	```

### Preparation
1.  Please Follow the Orginal [SSD](https://github.com/weiliu89/caffe/tree/ssd) to do all the preparation works. You should have lmdb fils for VOC2007. Check the following two links exist or not. 
   
   	```Shell
   	ls $CAFFE_ROOT/examples
   	# $CAFFE_ROOT/examples/VOC0712/VOC0712_trainval_lmdb
   	# $CAFFE_ROOT/examples/VOC0712/VOC0712_test_lmdb
   	```
   
2.  Download the Resnet-101 models from the [Deep-Residual-Network](https://github.com/KaimingHe/deep-residual-networks).
    
	```Shell
	# creat the directory for ResNet-101
	cd $CAFFE_ROOT/models
	mkdir ResNet-101
	# Rename the Resnet-101 models and put in the ResNet-101 direcotry
	ls $CAFFE_ROOT/models/ResNet-101
	# $CAFFE_ROOT/models/ResNet-101/ResNet-101-model.caffemodel
	# $CAFFE_ROOT/models/ResNet-101/ResNet-101-deploy.prototxt
	```

	
	
   

	
	
  
