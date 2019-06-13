 
/** Increment the HEAD */
        unsigned long new = *index + delta;
        barrier();
        *index = (new >= (short_buffer + PAGE_SIZE)) ? short_buffer : new;

/** Irq Handler */
    irqreturn_t short_interrupt(irq, void *dev_id, strwct pt_ress *regs){
        struct timeval tv; 
        int written; 

    /*  Write something here */
    
        short_incr_bp(&short_head, written);
        wake_up_interruptible(&short_queue);
        return IRQ_HANDLED;
    }
