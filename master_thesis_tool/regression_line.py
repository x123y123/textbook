import numpy as np
import matplotlib as plt
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures

# x_feature
x = np.array([2360, 2380, 2400, 2420, 2440, 2460, 2480, 2500, 2520, 2540, 2560, 2580, 2600, 2620, 2640, 2660]).reshape(-1, 1)
# y_feature
y = np.array([0.036, 0.053, 0.072, 0.09, 0.116, 0.148, 0.197, 0.238, 0.291, 0.404, 0.497, 0.645, 0.777, 0.954, 1.118, 1.296])
# regression_line range
test = np.arange(2000, 3000, 1, int).reshape(-1, 1)

# generate polynomial and interaction features
poly = PolynomialFeatures(degree=2, include_bias=False)

# calculate Eigenvalue
poly_features = poly.fit_transform(x)
# linear regression
poly_reg_model = LinearRegression()
poly_reg_model.fit(poly_features, y)

test_features = poly.fit_transform(test)

y_predicted = poly_reg_model.predict(poly_features)
test_predicted = poly_reg_model.predict(test_features)

# coef: const of x parameter , intercept: const 
print(poly_reg_model.coef_[:], poly_reg_model.intercept_) 

plt.pyplot.figure(figsize=(10, 6))
plt.title("Polynomial regression:)", size=16)
plt.scatter(x, y)
plt.plot(test, test_predicted, color="red")
plt.show()

