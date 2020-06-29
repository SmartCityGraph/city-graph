# Онтология Citygraph версия 1.2.200630

**citygraph- ... .owl содержит:**

- Классы

- Data/Object properties

- annotations

- ключевые индивиды, которые используются другими индивидами

**citygraph-  ... .ttl содержит:**

- Все что есть в citygraph.owl

**citygraph-1.1.200610-vasileostrovskiy-full.ttl содержит:**

- см. предыдущие версии


## Изменения вносили

- VV - Vitaly Vlasov

- MM - Maxim Matunkin

## Изменения

*Изменено:*

- Адрес вынесен на верхний уровень

- Справочник вынесен на верхний уровень

- MajorRenovation и WorkType переехал в Action


*Добавлено:*

- На верхний уровень добавлены Action (+подклассы), Procedure, Event, Document (+подклассы)

- Новые классы (Gren, Bush, Position, MilitaryObject, классы культурных объектов, образования, медицины, общественные объекты, вокзалы, сады, скверы, почта, пожарная станция)

- добавлены новые подклассы StreetFurniture (более 10 шт)

- В физические объекты добавлен новый класс Component - он описывает такие элементы городской среды, как ландшафт, покрытия, полоса движения, рельеф и пр. можно дальше развивать. В NetObject добавлены подклассы для описания сетевых объектов

- Добавлены Components для описания элементов городской среды (ландшафт, покрытие, полоса и пр)

- Новые проперти -  hasComp (hasSurface), hasPosition (hasCompanyPosition), hasAddressObj (hasStreet, hasAdmUnit), hasSubDoc, hasNetProperty (adjoin), hasAddress (hasHouseNumber, hasKorpus, hasLitera), hasDocument (hasDocDate, hasDocTitle), hasCulturalStatus (hasLocalMeaning, hasWorldMeaning, hasRegionalMeaning, hasFederalMeaning), hasReligiousObjectCharacteristic (hasDenomination, hasReligious)

*Удалены:*

- Служебная сущность 
- Tree заменен на Green
- Техника
- OtherFunctionalCityObject