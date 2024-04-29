#include <GUICSR.hpp>

#include <imgui.h>

#include <unordered_map>
#include <format>
#include <array>
#include <tuple>
#include <string>

void GUICSR::Draw() {
    using CSRTuple = std::tuple<uint32_t, std::string, bool>;
    using VM = VirtualMachine;
    
    static std::array csrs_names = {
        CSRTuple(VM::CSR_FFLAGS, "fflags", false),
        CSRTuple(VM::CSR_FRM, "frm", false),
        CSRTuple(VM::CSR_FCSR, "fcsr", false),
        CSRTuple(VM::CSR_CYCLE, "cycle", false),
        CSRTuple(VM::CSR_TIME, "time", false),
        CSRTuple(VM::CSR_INSTRET, "instret", false),
        CSRTuple(VM::CSR_HPMCOUNTER, "hpmcounter3", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 1, "hpmcounter4", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 2, "hpmcounter5", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 3, "hpmcounter6", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 4, "hpmcounter7", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 5, "hpmcounter8", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 6, "hpmcounter9", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 7, "hpmcounter10", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 8, "hpmcounter11", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 9, "hpmcounter12", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 10, "hpmcounter13", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 11, "hpmcounter14", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 12, "hpmcounter15", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 13, "hpmcounter16", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 14, "hpmcounter17", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 15, "hpmcounter18", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 16, "hpmcounter19", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 17, "hpmcounter20", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 18, "hpmcounter21", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 19, "hpmcounter22", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 20, "hpmcounter23", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 21, "hpmcounter24", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 22, "hpmcounter25", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 23, "hpmcounter26", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 24, "hpmcounter27", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 25, "hpmcounter28", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 26, "hpmcounter29", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 27, "hpmcounter30", false),
        CSRTuple(VM::CSR_HPMCOUNTER + 28, "hpmcounter31", false),
        CSRTuple(VM::CSR_CYCLEH, "cycleh", false),
        CSRTuple(VM::CSR_TIMEH, "timeh", false),
        CSRTuple(VM::CSR_INSTRETH, "instreth", false),
        CSRTuple(VM::CSR_HPMCOUNTERH, "hpmcounter3h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 1, "hpmcounter4h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 2, "hpmcounter5h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 3, "hpmcounter6h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 4, "hpmcounter7h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 5, "hpmcounter8h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 6, "hpmcounter9h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 7, "hpmcounter10h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 8, "hpmcounter11h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 9, "hpmcounter12h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 10, "hpmcounter13h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 11, "hpmcounter14h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 12, "hpmcounter15h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 13, "hpmcounter16h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 14, "hpmcounter17h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 15, "hpmcounter18h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 16, "hpmcounter19h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 17, "hpmcounter20h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 18, "hpmcounter21h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 19, "hpmcounter22h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 20, "hpmcounter23h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 21, "hpmcounter24h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 22, "hpmcounter25h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 23, "hpmcounter26h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 24, "hpmcounter27h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 25, "hpmcounter28h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 26, "hpmcounter29h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 27, "hpmcounter30h", false),
        CSRTuple(VM::CSR_HPMCOUNTERH + 28, "hpmcounter31h", false),
        CSRTuple(VM::CSR_SSTATUS, "sstatus", false),
        CSRTuple(VM::CSR_SIE, "sie", false),
        CSRTuple(VM::CSR_STVEC, "stvec", false),
        CSRTuple(VM::CSR_SCOUNTEREN, "scounteren", false),
        CSRTuple(VM::CSR_SENVCFG, "senvcfg", false),
        CSRTuple(VM::CSR_SSCRATCH, "sscratch", false),
        CSRTuple(VM::CSR_SEPC, "sepc", false),
        CSRTuple(VM::CSR_SCAUSE, "scause", false),
        CSRTuple(VM::CSR_STVAL, "stval", false),
        CSRTuple(VM::CSR_SIP, "sip", false),
        CSRTuple(VM::CSR_SATP, "satp", false),
        CSRTuple(VM::CSR_SCONTEXT, "scontext", false),
        CSRTuple(VM::CSR_MVENDORID, "mvendorid", false),
        CSRTuple(VM::CSR_MARCHID, "marchid", false),
        CSRTuple(VM::CSR_MIMPID, "mimpid", false),
        CSRTuple(VM::CSR_MHARTID, "mhartid", false),
        CSRTuple(VM::CSR_MCONFIGPTR, "mconfigptr", false),
        CSRTuple(VM::CSR_MSTATUS, "mstatus", false),
        CSRTuple(VM::CSR_MISA, "misa", true),
        CSRTuple(VM::CSR_MEDELEG, "medeleg", false),
        CSRTuple(VM::CSR_MIDELEG, "mideleg", false),
        CSRTuple(VM::CSR_MIE, "mie", false),
        CSRTuple(VM::CSR_MTVEC, "mtvec", false),
        CSRTuple(VM::CSR_MCOUNTEREN, "mcounteren", false),
        CSRTuple(VM::CSR_MSTATUSH, "mstatush", false),
        CSRTuple(VM::CSR_MSCRATCH, "mscratch", false),
        CSRTuple(VM::CSR_MEPC, "mepc", false),
        CSRTuple(VM::CSR_MCAUSE, "mcause", false),
        CSRTuple(VM::CSR_MTVAL, "mtval", false),
        CSRTuple(VM::CSR_MIP, "mip", false),
        CSRTuple(VM::CSR_MTINST, "mtinst", false),
        CSRTuple(VM::CSR_MTVAL2, "mtval2", false),
        CSRTuple(VM::CSR_MENVCFG, "menvcfg", false),
        CSRTuple(VM::CSR_MENVCFGH, "menvcfgh", false),
        CSRTuple(VM::CSR_MSECCFG, "mseccfg", false),
        CSRTuple(VM::CSR_MSECCFGH, "mseccfgh", false),
        CSRTuple(VM::CSR_PMPCFG0, "pmpcfg0", false),
        CSRTuple(VM::CSR_PMPCFG0 + 1, "pmpcfg1", false),
        CSRTuple(VM::CSR_PMPCFG0 + 2, "pmpcfg2", false),
        CSRTuple(VM::CSR_PMPCFG0 + 3, "pmpcfg3", false),
        CSRTuple(VM::CSR_PMPCFG0 + 4, "pmpcfg4", false),
        CSRTuple(VM::CSR_PMPCFG0 + 5, "pmpcfg5", false),
        CSRTuple(VM::CSR_PMPCFG0 + 6, "pmpcfg6", false),
        CSRTuple(VM::CSR_PMPCFG0 + 7, "pmpcfg7", false),
        CSRTuple(VM::CSR_PMPCFG0 + 8, "pmpcfg8", false),
        CSRTuple(VM::CSR_PMPCFG0 + 9, "pmpcfg9", false),
        CSRTuple(VM::CSR_PMPCFG0 + 10, "pmpcfg10", false),
        CSRTuple(VM::CSR_PMPCFG0 + 11, "pmpcfg11", false),
        CSRTuple(VM::CSR_PMPCFG0 + 12, "pmpcfg12", false),
        CSRTuple(VM::CSR_PMPCFG0 + 13, "pmpcfg13", false),
        CSRTuple(VM::CSR_PMPCFG0 + 14, "pmpcfg14", false),
        CSRTuple(VM::CSR_PMPCFG0 + 15, "pmpcfg15", false),
        CSRTuple(VM::CSR_PMPADDR0, "pmpaddr0", false),
        CSRTuple(VM::CSR_PMPADDR0 + 1, "pmpaddr1", false),
        CSRTuple(VM::CSR_PMPADDR0 + 2, "pmpaddr2", false),
        CSRTuple(VM::CSR_PMPADDR0 + 3, "pmpaddr3", false),
        CSRTuple(VM::CSR_PMPADDR0 + 4, "pmpaddr4", false),
        CSRTuple(VM::CSR_PMPADDR0 + 5, "pmpaddr5", false),
        CSRTuple(VM::CSR_PMPADDR0 + 6, "pmpaddr6", false),
        CSRTuple(VM::CSR_PMPADDR0 + 7, "pmpaddr7", false),
        CSRTuple(VM::CSR_PMPADDR0 + 8, "pmpaddr8", false),
        CSRTuple(VM::CSR_PMPADDR0 + 9, "pmpaddr9", false),
        CSRTuple(VM::CSR_PMPADDR0 + 10, "pmpaddr10", false),
        CSRTuple(VM::CSR_PMPADDR0 + 11, "pmpaddr11", false),
        CSRTuple(VM::CSR_PMPADDR0 + 12, "pmpaddr12", false),
        CSRTuple(VM::CSR_PMPADDR0 + 13, "pmpaddr13", false),
        CSRTuple(VM::CSR_PMPADDR0 + 14, "pmpaddr14", false),
        CSRTuple(VM::CSR_PMPADDR0 + 15, "pmpaddr15", false),
        CSRTuple(VM::CSR_PMPADDR0 + 16, "pmpaddr16", false),
        CSRTuple(VM::CSR_PMPADDR0 + 17, "pmpaddr17", false),
        CSRTuple(VM::CSR_PMPADDR0 + 18, "pmpaddr18", false),
        CSRTuple(VM::CSR_PMPADDR0 + 19, "pmpaddr19", false),
        CSRTuple(VM::CSR_PMPADDR0 + 20, "pmpaddr20", false),
        CSRTuple(VM::CSR_PMPADDR0 + 21, "pmpaddr21", false),
        CSRTuple(VM::CSR_PMPADDR0 + 22, "pmpaddr22", false),
        CSRTuple(VM::CSR_PMPADDR0 + 23, "pmpaddr23", false),
        CSRTuple(VM::CSR_PMPADDR0 + 24, "pmpaddr24", false),
        CSRTuple(VM::CSR_PMPADDR0 + 25, "pmpaddr25", false),
        CSRTuple(VM::CSR_PMPADDR0 + 26, "pmpaddr26", false),
        CSRTuple(VM::CSR_PMPADDR0 + 27, "pmpaddr27", false),
        CSRTuple(VM::CSR_PMPADDR0 + 28, "pmpaddr28", false),
        CSRTuple(VM::CSR_PMPADDR0 + 29, "pmpaddr29", false),
        CSRTuple(VM::CSR_PMPADDR0 + 30, "pmpaddr30", false),
        CSRTuple(VM::CSR_PMPADDR0 + 31, "pmpaddr31", false),
        CSRTuple(VM::CSR_PMPADDR0 + 32, "pmpaddr32", false),
        CSRTuple(VM::CSR_PMPADDR0 + 33, "pmpaddr33", false),
        CSRTuple(VM::CSR_PMPADDR0 + 34, "pmpaddr34", false),
        CSRTuple(VM::CSR_PMPADDR0 + 35, "pmpaddr35", false),
        CSRTuple(VM::CSR_PMPADDR0 + 36, "pmpaddr36", false),
        CSRTuple(VM::CSR_PMPADDR0 + 37, "pmpaddr37", false),
        CSRTuple(VM::CSR_PMPADDR0 + 38, "pmpaddr38", false),
        CSRTuple(VM::CSR_PMPADDR0 + 39, "pmpaddr39", false),
        CSRTuple(VM::CSR_PMPADDR0 + 40, "pmpaddr40", false),
        CSRTuple(VM::CSR_PMPADDR0 + 41, "pmpaddr41", false),
        CSRTuple(VM::CSR_PMPADDR0 + 42, "pmpaddr42", false),
        CSRTuple(VM::CSR_PMPADDR0 + 43, "pmpaddr43", false),
        CSRTuple(VM::CSR_PMPADDR0 + 44, "pmpaddr44", false),
        CSRTuple(VM::CSR_PMPADDR0 + 45, "pmpaddr45", false),
        CSRTuple(VM::CSR_PMPADDR0 + 46, "pmpaddr46", false),
        CSRTuple(VM::CSR_PMPADDR0 + 47, "pmpaddr47", false),
        CSRTuple(VM::CSR_PMPADDR0 + 48, "pmpaddr48", false),
        CSRTuple(VM::CSR_PMPADDR0 + 49, "pmpaddr49", false),
        CSRTuple(VM::CSR_PMPADDR0 + 50, "pmpaddr50", false),
        CSRTuple(VM::CSR_PMPADDR0 + 51, "pmpaddr51", false),
        CSRTuple(VM::CSR_PMPADDR0 + 52, "pmpaddr52", false),
        CSRTuple(VM::CSR_PMPADDR0 + 53, "pmpaddr53", false),
        CSRTuple(VM::CSR_PMPADDR0 + 54, "pmpaddr54", false),
        CSRTuple(VM::CSR_PMPADDR0 + 55, "pmpaddr55", false),
        CSRTuple(VM::CSR_PMPADDR0 + 56, "pmpaddr56", false),
        CSRTuple(VM::CSR_PMPADDR0 + 57, "pmpaddr57", false),
        CSRTuple(VM::CSR_PMPADDR0 + 58, "pmpaddr58", false),
        CSRTuple(VM::CSR_PMPADDR0 + 59, "pmpaddr59", false),
        CSRTuple(VM::CSR_PMPADDR0 + 60, "pmpaddr60", false),
        CSRTuple(VM::CSR_PMPADDR0 + 61, "pmpaddr61", false),
        CSRTuple(VM::CSR_PMPADDR0 + 62, "pmpaddr62", false),
        CSRTuple(VM::CSR_PMPADDR0 + 63, "pmpaddr63", false),
        CSRTuple(VM::CSR_MCYCLE, "mcycle", false),
        CSRTuple(VM::CSR_MINSTRET, "minstret", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3, "mhpmcounter3", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 1, "mhpmcounter4", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 2, "mhpmcounter5", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 3, "mhpmcounter6", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 4, "mhpmcounter7", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 5, "mhpmcounter8", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 6, "mhpmcounter9", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 7, "mhpmcounter10", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 8, "mhpmcounter11", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 9, "mhpmcounter12", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 10, "mhpmcounter13", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 11, "mhpmcounter14", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 12, "mhpmcounter15", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 13, "mhpmcounter16", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 14, "mhpmcounter17", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 15, "mhpmcounter18", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 16, "mhpmcounter19", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 17, "mhpmcounter20", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 18, "mhpmcounter21", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 19, "mhpmcounter22", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 20, "mhpmcounter23", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 21, "mhpmcounter24", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 22, "mhpmcounter25", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 23, "mhpmcounter26", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 24, "mhpmcounter27", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 25, "mhpmcounter28", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 26, "mhpmcounter29", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 27, "mhpmcounter30", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3 + 28, "mhpmcounter31", false),
        CSRTuple(VM::CSR_MCYCLEH, "mcycleh", false),
        CSRTuple(VM::CSR_MINSTRETH, "minstreth", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H, "mhpmcounter3h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 1, "mhpmcounter4h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 2, "mhpmcounter5h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 3, "mhpmcounter6h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 4, "mhpmcounter7h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 5, "mhpmcounter8h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 6, "mhpmcounter9h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 7, "mhpmcounter10h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 8, "mhpmcounter11h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 9, "mhpmcounter12h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 10, "mhpmcounter13h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 11, "mhpmcounter14h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 12, "mhpmcounter15h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 13, "mhpmcounter16h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 14, "mhpmcounter17h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 15, "mhpmcounter18h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 16, "mhpmcounter19h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 17, "mhpmcounter20h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 18, "mhpmcounter21h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 19, "mhpmcounter22h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 20, "mhpmcounter23h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 21, "mhpmcounter24h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 22, "mhpmcounter25h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 23, "mhpmcounter26h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 24, "mhpmcounter27h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 25, "mhpmcounter28h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 26, "mhpmcounter29h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 27, "mhpmcounter30h", false),
        CSRTuple(VM::CSR_MHPMCOUNTER3H + 28, "mhpmcounter31h", false),
        CSRTuple(VM::CSR_MCOUNTINHIBIT, "mcountinhibit", false),
        CSRTuple(VM::CSR_MHPMEVENT3, "mhpmevent3", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 1, "mhpmevent4", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 2, "mhpmevent5", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 3, "mhpmevent6", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 4, "mhpmevent7", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 5, "mhpmevent8", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 6, "mhpmevent9", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 7, "mhpmevent10", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 8, "mhpmevent11", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 9, "mhpmevent12", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 10, "mhpmevent13", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 11, "mhpmevent14", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 12, "mhpmevent15", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 13, "mhpmevent16", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 14, "mhpmevent17", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 15, "mhpmevent18", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 16, "mhpmevent19", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 17, "mhpmevent20", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 18, "mhpmevent21", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 19, "mhpmevent22", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 20, "mhpmevent23", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 21, "mhpmevent24", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 22, "mhpmevent25", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 23, "mhpmevent26", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 24, "mhpmevent27", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 25, "mhpmevent28", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 26, "mhpmevent29", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 27, "mhpmevent30", false),
        CSRTuple(VM::CSR_MHPMEVENT3 + 28, "mhpmevent31", false)
    };

    if (ImGui::Begin("CSRs")) {
        std::unordered_map<uint32_t, uint32_t> csrs;
        vm.GetCSRSnapshot(csrs);

        for (const auto& [csr, name, binary] : csrs_names) {
            if (binary)
                ImGui::Text("%-16s0x%-3x : 0x%08x (%s)", name.c_str(), csr, csrs[csr], std::format("{:b}", csrs[csr]).c_str());
            else
                ImGui::Text("%-16s0x%-3x : 0x%08x (%u)", name.c_str(), csr, csrs[csr], csrs[csr]);
        }
    }

    ImGui::End();
}