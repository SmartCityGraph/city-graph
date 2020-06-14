# Онтология Cityont-Core версия 1.1.200521

**cityont-core- ... .owl содержит:**

- Классы

- Data/Object properties

- annotations

- ключевые индивиды, которые используются другими индивидами (например, группы жителей)

**cityont-core-  ... .ttl содержит:**

- Все что есть в cityont-core.owl

- Ключевые индивиды по проекту House (в том числе: управляющие компании, виды работ капитального ремонта и некоторые др.)

**cityont-core-1.1.200525-OKATO-ttl.zip содержит:**

- Все что есть в cityont-core.owl

- Только индивиды OKATO и AdministrativeUnits (индивидов ОКТМО нет, отдельно их можно взять в папке TTL)

**cityont-core-1.1.200525-OKTMO-ttl.zip содержит:**

- Все что есть в cityont-core.owl

- Только индивиды OKTMO и AdministrativeUnits (индивидов OKATO нет, отдельно их можно взять в папке TTL)

**cityont-core-1.1.200521-extended.ttl содержит:**

- Можно использовать с прошлой версии

## Изменения вносили

- VV - Vitaly Vlasov

- MM - Maxim Matunkin

## Изменения

*Изменено:*

- Классу "Region" добавлен атрибут hasOKTMO

- Класс "FederalOkrug" перенесён из класса "Municipality" в "AdministrtiveUnit"

- ObjectProperty "includedIn" добавлены область определения и область значения в виде класса "PhysicalObject"

- Исправлены грамматические ошибки

*Добавлено:*

- Индивиды ОКАТО, ОКТМО и AdministrativeUnits на основе данныхь сайта Росстата (от 20 мая 2020)

- В класс "Municipality" добавлены подклассы "AutonomousOkrugMunicipality", "InterSettlementTerritory" и "UrbanDistrict"

- Добавлены атрибуты hasAbbr, hasOKLevel(а также субатрибуты hasOKLevel1, hasOKLeve2, hasOKLeve3, hasOKLevel4), hasStringValue, hasAdministrativeCenter, hasInitiationDate 

*Удалены:*

- Нет