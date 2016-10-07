# FP16 version of Single Shot Multibox Detector(SSD)
   This branch tries to run SSD on FP16 version of Caffe in Jetson TX1 platform.  
   The accuracy is not guaranteed, due to no finetune the model in fp16. 


Check out the [ssd](https://github.com/weiliu89/caffe/tree/ssd) , [FP16](https://github.com/NVIDIA/caffe/tree/experimental/fp16)
     
## Execution 

1. Download the SSD 300 models trained on Pascal VOC and MSCOCO in [ssd](https://github.com/weiliu89/caffe/tree/ssd)

2. Use webcam demo code
  ```Shell
  python examples/ssd/ssd_pascal_webcam.py  
  # Execute in fp16 mode
  python examples/ssd/ssd_pascal_webcam.py fp16 
  ```

## Citation of SSD
Please cite SSD in your publications if it helps your research:

     @article{liu15ssd,
       Title = {{SSD}: Single Shot MultiBox Detector},
       Author = {Liu, Wei and Anguelov, Dragomir and Erhan, Dumitru and Szegedy, Christian and Reed, Scott and Fu, Cheng-Yang and Berg, Alexander C.},
       Journal = {arXiv preprint arXiv:1512.02325},
       Year = {2015}
     }
