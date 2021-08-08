global read_eip
read_eip:
    pop eax                     
    jmp eax                    
                          

global copy_page_physical
copy_page_physical:
    push ebx              
    pushf                             
    cli                   
    mov ebx, [esp+12]    
    mov ecx, [esp+16]     
    mov edx, cr0          
    and edx, 0x7fffffff  
    mov cr0, edx          
    mov edx, 1024        
  
.loop:
    mov eax, [ebx]        
    mov [ecx], eax        
    add ebx, 4            
    add ecx, 4            
    dec edx               
    jnz .loop             
    
    mov edx, cr0          
    or  edx, 0x80000000  
    mov cr0, edx          
    
    popf                  
    pop ebx               
    ret
