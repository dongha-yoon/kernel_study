cmd_/home/donghayoon/Kernel_study/Module.symvers := sed 's/ko$$/o/' /home/donghayoon/Kernel_study/modules.order | scripts/mod/modpost  -a   -o /home/donghayoon/Kernel_study/Module.symvers -e -i Module.symvers   -T -