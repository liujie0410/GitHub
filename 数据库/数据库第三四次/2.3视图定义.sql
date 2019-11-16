/* ”Õº∂®“Â*/
CREATE VIEW vwOrderWrapper
     AS
     SELECT cOrderNo, cToyId, siQty, vDescription, mWrapperRate
     FROM OrderDetail JOIN Wrapper
     ON OrderDetail.cWrapperId = Wrapper.cWrapperId


