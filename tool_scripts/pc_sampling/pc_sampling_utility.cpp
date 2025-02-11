#include "pc_sampling_utility_helper.h"

int main(int argc, char *argv[])
{
    CUpti_PCSamplingData *mergedPcSampDataBuffer = NULL;
    size_t numMergedPcSampDataBuffer = 0;

    Init();
    ParseCommandLineArgs(argc, argv);
    FillCrcModuleMap();
    RetrievePcSampData();

    if (!disableSourceCorrelation)
    {
        if (!disableMerge && collectionMode != CUPTI_PC_SAMPLING_COLLECTION_MODE_KERNEL_SERIALIZED)
        {
            MergePcSampDataBuffers(&mergedPcSampDataBuffer, numMergedPcSampDataBuffer);
            SourceCorrelation(mergedPcSampDataBuffer, numMergedPcSampDataBuffer);
        }
        else
        {
            SourceCorrelation(buffersRetrievedDataVector.data(), buffersRetrievedDataVector.size());
        }
    }
    else
    {
        if (!disablePcInfoPrints)
        {
            PrintRetrievedPcSampData();
        }
    }

    // Free memory
    FreePcSampStallReasonsMemory();
    FreePcSampDataBuffers(mergedPcSampDataBuffer, numMergedPcSampDataBuffer);
    FreePcSampDataBuffers(buffersRetrievedDataVector.data(), buffersRetrievedDataVector.size());
    FreeCrcModuleMapMemory();

    return 0;
}
