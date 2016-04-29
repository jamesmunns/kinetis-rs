var group__spi__hal =
[
    [ "spi_status_t", "group__spi__hal.html#ga856ecadf3d7fe18c4fc3ae56500f8982", [
      [ "kStatus_SPI_SlaveTxUnderrun", "group__spi__hal.html#gga856ecadf3d7fe18c4fc3ae56500f8982a3aa575be3ede4f8eddabf55b3f4a9664", null ],
      [ "kStatus_SPI_SlaveRxOverrun", "group__spi__hal.html#gga856ecadf3d7fe18c4fc3ae56500f8982ad2207018f8aa8c1fc60200cf3d7861cc", null ],
      [ "kStatus_SPI_Timeout", "group__spi__hal.html#gga856ecadf3d7fe18c4fc3ae56500f8982a496ced6fffc33d7bbeb01d203dfc4836", null ],
      [ "kStatus_SPI_Busy", "group__spi__hal.html#gga856ecadf3d7fe18c4fc3ae56500f8982a703abdf7900047c4d13536480f3463ab", null ],
      [ "kStatus_SPI_NoTransferInProgress", "group__spi__hal.html#gga856ecadf3d7fe18c4fc3ae56500f8982a9b2cf00def0d1d7af16ba45f5961e209", null ]
    ] ],
    [ "spi_master_slave_mode_t", "group__spi__hal.html#ga434258af00a12cef572d479de91f76e2", [
      [ "kSpiMaster", "group__spi__hal.html#gga434258af00a12cef572d479de91f76e2acbac46c94c0c7c713120dfc0e27c7ff0", null ],
      [ "kSpiSlave", "group__spi__hal.html#gga434258af00a12cef572d479de91f76e2a0f00448a47a24da9430b64f75f9a20de", null ]
    ] ],
    [ "spi_clock_polarity_t", "group__spi__hal.html#ga3e5a7cd043c9596779bc23b34cb3d1f9", [
      [ "kSpiClockPolarity_ActiveHigh", "group__spi__hal.html#gga3e5a7cd043c9596779bc23b34cb3d1f9a0b33c8e75da2f2c6a2e821f94cc77f46", null ],
      [ "kSpiClockPolarity_ActiveLow", "group__spi__hal.html#gga3e5a7cd043c9596779bc23b34cb3d1f9a41c5cc78a06ec9a47d2230244535ad38", null ]
    ] ],
    [ "spi_clock_phase_t", "group__spi__hal.html#ga9ad313685ade497f5cbcb71c74a1b4dc", [
      [ "kSpiClockPhase_FirstEdge", "group__spi__hal.html#gga9ad313685ade497f5cbcb71c74a1b4dcaac180df70db6fa5463501e6b7a38a183", null ],
      [ "kSpiClockPhase_SecondEdge", "group__spi__hal.html#gga9ad313685ade497f5cbcb71c74a1b4dca58859ca1e960ebb8f6e1121997c6fbbe", null ]
    ] ],
    [ "spi_shift_direction_t", "group__spi__hal.html#gaa68518c16202382c2e1f1c7c66a9d53d", [
      [ "kSpiMsbFirst", "group__spi__hal.html#ggaa68518c16202382c2e1f1c7c66a9d53daefa27165c331b1503fd02a79099e8dfe", null ],
      [ "kSpiLsbFirst", "group__spi__hal.html#ggaa68518c16202382c2e1f1c7c66a9d53dad0909dc10154689a11543cc01f4815ad", null ]
    ] ],
    [ "spi_ss_output_mode_t", "group__spi__hal.html#ga2e5a238c65f35a2d82cc1c55927030fe", [
      [ "kSpiSlaveSelect_AsGpio", "group__spi__hal.html#gga2e5a238c65f35a2d82cc1c55927030fea771df87a27a63668dea1cd3573f9a821", null ],
      [ "kSpiSlaveSelect_FaultInput", "group__spi__hal.html#gga2e5a238c65f35a2d82cc1c55927030fea7a158d51735115f93647f4a523dae0b3", null ],
      [ "kSpiSlaveSelect_AutomaticOutput", "group__spi__hal.html#gga2e5a238c65f35a2d82cc1c55927030feaa825f6b317d71b52432b265a47201cc6", null ]
    ] ],
    [ "spi_pin_mode_t", "group__spi__hal.html#gab55fee4d636428392047e3355f33a36f", [
      [ "kSpiPinMode_Normal", "group__spi__hal.html#ggab55fee4d636428392047e3355f33a36fa5fae1212c85e103914ae3bb0c6d96aff", null ],
      [ "kSpiPinMode_Input", "group__spi__hal.html#ggab55fee4d636428392047e3355f33a36fa2f3d4b10e84461dedc8351adaf6bebb3", null ],
      [ "kSpiPinMode_Output", "group__spi__hal.html#ggab55fee4d636428392047e3355f33a36faf46381ed47d439757bcfb172337c405a", null ]
    ] ],
    [ "SPI_HAL_Init", "group__spi__hal.html#ga231fc2c7a0ab45610b3868e1a5eec579", null ],
    [ "SPI_HAL_Enable", "group__spi__hal.html#ga1527060bb58c6cd31d47889461fda6da", null ],
    [ "SPI_HAL_Disable", "group__spi__hal.html#ga32b7481a6e6619f11daeae7a681fb38d", null ],
    [ "SPI_HAL_SetBaud", "group__spi__hal.html#gad4d57db38d70b48df76510caeccd1f3a", null ],
    [ "SPI_HAL_SetBaudDivisors", "group__spi__hal.html#ga4c37bf112e4b9820001a017da96f28f3", null ],
    [ "SPI_HAL_SetMasterSlave", "group__spi__hal.html#ga1c155bea47506b6508d26b75d3a3cc36", null ],
    [ "SPI_HAL_IsMaster", "group__spi__hal.html#gab31e2796b856549174d72f21bd272c73", null ],
    [ "SPI_HAL_SetSlaveSelectOutputMode", "group__spi__hal.html#gaa7f8935e3b28e31dc4aa31654f0005fb", null ],
    [ "SPI_HAL_SetDataFormat", "group__spi__hal.html#ga72ccf199bd5e0ac73f28cacd4db9e613", null ],
    [ "SPI_HAL_SetPinMode", "group__spi__hal.html#gaaa5fe2860de16790fcf93d6e7e58e3c3", null ],
    [ "SPI_HAL_SetTxDmaCmd", "group__spi__hal.html#ga96da2a2b002f8628859f7e87a12455b2", null ],
    [ "SPI_HAL_SetRxDmaCmd", "group__spi__hal.html#ga8f16ceb07175af89ec78f03088747180", null ],
    [ "SPI_HAL_ConfigureStopInWaitMode", "group__spi__hal.html#ga955f44480f054d13affe722b69a73174", null ],
    [ "SPI_HAL_SetReceiveAndFaultIntCmd", "group__spi__hal.html#ga0e20c2e0e994cbe8a56160481c604ebb", null ],
    [ "SPI_HAL_SetTransmitIntCmd", "group__spi__hal.html#ga481cd204567237f82957e2c603fac1b2", null ],
    [ "SPI_HAL_SetMatchIntCmd", "group__spi__hal.html#ga16aa2590f43aadfae5f92d22e269956f", null ],
    [ "SPI_HAL_IsReadBuffFullPending", "group__spi__hal.html#ga57ac3bdd2f849f4a297275fe4e6d1391", null ],
    [ "SPI_HAL_IsTxBuffEmptyPending", "group__spi__hal.html#gae81751b428d2cfdb897fde38dab8e856", null ],
    [ "SPI_HAL_IsModeFaultPending", "group__spi__hal.html#ga78aa61b00284f2116f7f639c353a3be6", null ],
    [ "SPI_HAL_ClearModeFaultFlag", "group__spi__hal.html#ga313129f88cc7366aac211e288f96b895", null ],
    [ "SPI_HAL_IsMatchPending", "group__spi__hal.html#ga13be251dc4119d918e35e6e2ac399166", null ],
    [ "SPI_HAL_ClearMatchFlag", "group__spi__hal.html#ga8de9fb436a2bba000580cf10cda345d6", null ],
    [ "SPI_HAL_ReadData", "group__spi__hal.html#ga3965ae45f7844beed2e9a42417c87dc8", null ],
    [ "SPI_HAL_WriteData", "group__spi__hal.html#ga167911e1a4f78edc42e2abfe5a7bd18a", null ],
    [ "SPI_HAL_WriteDataBlocking", "group__spi__hal.html#gaefb82045a5221c712148625906a42563", null ],
    [ "SPI_HAL_SetMatchValue", "group__spi__hal.html#ga4308b8c93aa49880968c1f1fb7187772", null ]
];