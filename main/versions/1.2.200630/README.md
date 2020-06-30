# Онтология Citygraph версия 1.2.200630

**citygraph-1.2.200630.owl содержит:**

- Классы

- Data/Object properties

- annotations

- ключевые индивиды, которые используются другими индивидами

**citygraph-1.2.200630.ttl содержит:**

- Все что есть в citygraph.owl

**citygraph-1.1.200630-vasileostrovskiy-full.ttl содержит:**

- Индивиды CapitalConstruction, LivingObject, MajorRenovation, ManagingOrganization, Address, Street, WorkType и Geometry всех домов Василеостровского района.


## Изменения вносили

- VV - Vitaly Vlasov

- MM - Maxim Matunkin

## Изменения

*Изменено:*

- Лэйблы на русском языке приведены в соответствии со стандартом

- Некоторые проперти были переименованы в "topData...", что изменило их статус в онтологии, теперь можно использовать только их дочерние проперти, но не их сами.

- Переименованы некоторые проперти и переназначены их области определения. hasIllumination и needElectricity стали дочерними проперти от topDataArchElement

- Переименованы некоторые классы (например Surface переименован в Covering)

- Исправлены некоторые грамматические ошибки

*Добавлено:*

- Новые классы (AirSpaceObject, Boulevard, Forest (CityForest, ConservancyArea, ForestPark, ForestReserve),GroundObject, ZNOP, Reservoir, OOPT (BotanicGarden, ConservancyArea, ForestReserve, NationalPark, NatureMonument, NaturePark), Forestry, DrinkFontain, GreenRoof, Skalodrom, Sportground, VerticalGreen, SmallCityGarden, SmallGardenInBlock

- Новые проперти - hasGovStatus topDataNature (hasCoastalProtectiveStrip, hasLength, hasWaterSafeZone), topEcologyParam (hasIlluminationPollution, hasPM10value, hasPM25value, hasRadioactivePollution), 

*Удалены:*

- Индивиды Управляющих Компаний и Видов работ