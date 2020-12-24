cmd_/home/donghayoon/Kernel_study/modules.order := {   echo /home/donghayoon/Kernel_study/module_example2.ko; :; } | awk '!x[$$0]++' - > /home/donghayoon/Kernel_study/modules.order
