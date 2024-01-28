#pragma once

#include <buffalo/types.h>

namespace buffalo {

class GlobalDescriptorTable {
private:
    class SegmentDescriptor {
    private:
        uint16_t limit_lo;
        uint16_t base_lo;
        uint8_t base_hi;
        uint8_t type;
        uint8_t limit_hi;
        uint8_t base_vhi;
    public:
        SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
        uint32_t Base();
        uint32_t Limit();
    } __attribute__((packed));

    /**
     * @brief A segment descriptor representing a null segment.
     * This is typically used as the first entry in the GDT and does not point to any valid memory segment
     * 
     */
    SegmentDescriptor null_segment_selector;
    /**
     * @brief A segment descriptor reserved for future use or a placeholder.
     * 
     */
    SegmentDescriptor unused_segment_selector;

    /**
     * @brief A segment descriptor for the code segment, where executable code is stored.
     * 
     */
    SegmentDescriptor code_segment_selector;
    /**
     * @brief A segment descriptor for the data segment, where data is stored.
     * 
     */
    SegmentDescriptor data_segment_selector;
public:
    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    uint16_t CodeSegmentSelector();
    uint16_t DataSegmentSelector();
};
}