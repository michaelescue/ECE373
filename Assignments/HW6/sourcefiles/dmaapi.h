/**
 * @file dmaapi.h
 * @author your name (me
 * @brief 
 * @version 0.1
 * @date 2019-06-11
 * 
 * Steps to initialize:
 * Reset Device
 * Create descriptors
 * Set promiscuous mode
 * Set autoneg speed
 * Force link up
 * Start interrupt handlers
 * 
 */


/** Descriptor struct */
    struct tx_desc{
        __le64 buffer_addr;
        union{
            __le16 length;      // 16-bit   length
                struct{
                u8 cso;         // 8-bit    cso
                u8 cmd;         // 8-bit    cmd
            }flags;         
        }lower; 
        union{
            __le32 data;        // 32-bit   data
            struct{
                u8 status;      // 8-bit    status
                u8 css;         // 8-bit    css
                __le16 special; // 16-bit   special
            }fields;
        }upper
    }


/** From Wed May 15 Lecture By
 * 
 */

/** Move-data function */
    static void ece_move_my_data(struct dev mydev, int len, unsigned char *buf, void *hw_addr){
        dma_addr_t daddr;
        unsigned int reg;
        unsigned char *pmem;

    /*  Pin existing buffer */
        daddr = dma_map_single(mydev, buf, len, DMA_TO_DEVICE);

    /*  Tell the device where the DMA space is */
        reg = (daddr >> 32) & 0xffffffff;
        writel(reg, hw_addr + ECE_DMA_HI_REGISTER);
        reg = daddr & 0xffffffff;
        writel(reg, hw_addr + ECE_DMA_HI_REGISTER);

    /*  Tell the device to copy the data    */
        reg = 1;
        writel(reg, hw_addr + ECE_READ_DOORBELL);

    /*  Interrupt-Wait for DMA to complete */
    /* Unpin memory */
        dma_unmap_single(mydev, daddr, len, DMA_TO_DEVICE);
    }


/** Buffer states:
 * 
 * 
 * done
 * ready to send    (driver)
 * next to use      (driver)
 * next_to_clean    (interrupt)
 * HEAD     
 * TAIL      
 * 
 * There will be two Descriptor Rings:
 * tx_ring
 * rx_ring
 * 
 */

/** Filling Out a ring */
    do{
        buffer_info = &tx_ring->buffer_info[i];
        tx_desc = E1000_TX_DESC(*tx_ring, i);
        tx_desc->buffer_addr = cpu_to_le64(buffer_info->dma);
        tx_desc->lower.data = cpu_to_le32(txd_lower | buffer_info->length);
        tx_desc->upper.data = cpu_to_le32(txd_upper);

        i++;
        if (i == tx_ring->count)
            i=0;
    }while(--count > 0);

    tx_dexc->lower.data |= cpu_to_le32(adapter->txd_cmd);

    writel(i, E1000_TDT)); // Bumps tail.

