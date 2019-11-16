select vToyName,cCartId
from Toys
left outer join ShoppingCart
on Toys.cToyId=ShoppingCart.cToyId
