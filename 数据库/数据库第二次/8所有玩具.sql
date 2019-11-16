select vToyName,cBrandName,cCategory
from Toys,Category,ToyBrand
where Toys.cCategoryId=Category.cCategoryId and Toys.cBrandId=ToyBrand.cBrandId/*多表连接*/
