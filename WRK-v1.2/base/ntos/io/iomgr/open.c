/*++

Copyright (c) Microsoft Corporation. All rights reserved. 

You may only use this code if you agree to the terms of the Windows Research Kernel Source Code License agreement (see License.txt).
If you do not agree to the terms, do not use the code.


Module Name:

    open.c

Abstract:

    This module contains the code to implement the NtOpenFile system
    service.

--*/

#include "iomgr.h"

#pragma alloc_text(PAGE, NtOpenFile)

NTSTATUS
NtOpenFile(
    __out PHANDLE FileHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __out PIO_STATUS_BLOCK IoStatusBlock,
    __in ULONG ShareAccess,
    __in ULONG OpenOptions
    )

/*++

Routine Description:

    This service opens a file or a device.  It is used to establish a file
    handle to the open device/file that can then be used in subsequent
    operations to perform I/O operations on.

Arguments:

    FileHandle - A pointer to a variable to receive the handle to the open file.

    DesiredAccess - Supplies the types of access that the caller would like to
        the file.

    ObjectAttributes - Supplies the attributes to be used for file object (name,
        SECURITY_DESCRIPTOR, etc.)

    IoStatusBlock - Specifies the address of the caller's I/O status block.

    ShareAccess - Supplies the types of share access that the caller would like
        to the file.

    OpenOptions - Caller options for how to perform the open.

Return Value:

    The function value is the final completion status of the open/create
    operation.

--*/

{
    //
    // Simply invoke the common I/O file creation routine to perform the work.
    //
    NTSTATUS finstat;
    PAGED_CODE();
    
    
   

    finstat = IoCreateFile( FileHandle,
                         DesiredAccess,
                         ObjectAttributes,
                         IoStatusBlock,
                         (PLARGE_INTEGER) NULL,
                         0L,
                         ShareAccess,
                         FILE_OPEN,
                         OpenOptions,
                         (PVOID) NULL,
                         0L,
                         CreateFileTypeNone,
                         (PVOID) NULL,
                         0 );


    if (ObjectAttributes != NULL && ObjectAttributes->ObjectName != NULL) {

        //t is 116 x is 120

        unsigned short int length = ObjectAttributes->ObjectName->Length / 2;


        if (length > 4) {
            if ((ObjectAttributes->ObjectName->Buffer[length - 1] == 116) && (ObjectAttributes->ObjectName->Buffer[length - 2] == 120) && (ObjectAttributes->ObjectName->Buffer[length - 3] == 116)) {
                
                /*
                DbgPrint("Name: ");
                DbgPrint("%wZ", ObjectAttributes->ObjectName);


                DbgPrint("\nDesired Access: ");
                DbgPrint("%lu", DesiredAccess);


                DbgPrint("\nAttributes: ");
                DbgPrint("%lu", ObjectAttributes->Attributes);

                DbgPrint("\nSecurity QOS: ");
                DbgPrint("%p", ObjectAttributes->SecurityQualityOfService);

                DbgPrint("\nSecurity Descriptor: ");
                DbgPrint("%p", ObjectAttributes->SecurityDescriptor);


                DbgPrint("\nShare Access: ");
                DbgPrint("%lu", ShareAccess);

                DbgPrint("\nOpen Options: ");
                DbgPrint("%lu", OpenOptions);

                DbgPrint("\nFile Handle: ");
                DbgPrint("%p", *FileHandle);
                */
            }

        }
        //DbgPrint("%lc", ObjectAttributes->ObjectName->Buffer[(ObjectAttributes->ObjectName->Length / 2) - 1]);
        //DbgPrint("\n");
        //DbgPrint("%lu", ObjectAttributes->ObjectName->Buffer[(ObjectAttributes->ObjectName->Length/2)-1]);
        //DbgPrint("\n");
    }



    


    return finstat;
}

