import random
import numpy as np


class Iris:
    sepal_length = 0
    sepal_width = 0
    petal_length = 0
    petal_width = 0
    clasa = ''

    def __init__(self, sepal_length, sepal_width, petal_length, petal_width, clasa):
        self.sepal_length = float(sepal_length)
        self.sepal_width = float(sepal_width)
        self.petal_length = float(petal_length)
        self.petal_width = float(petal_width)
        self.clasa = clasa

    def __str__(self):
        return str(self.sepal_length) + ' ' + str(self.sepal_width) + ' ' + str(self.petal_length) + ' ' + str(
            self.petal_width) + ' ' + self.clasa


def read_file():
    f = open('iris.data')
    lista = []
    for line in f:
        line = line.strip()
        if line:
            lista.append(Iris(*line.split(',')))
    f.close()
    return lista


def convert_mat(mat):
    conv_mat = []
    for row in mat:
        conv_row = []
        for item in row.split(' '):
            try:
                conv_row.append(float(item))
            except ValueError as stupid_error:
                pass

        conv_mat.append(conv_row)
    return conv_mat


class NeuralNetwork:
    def __init__(self):
        self.rata_invatare = 0.1
        self.numar_maxim_epoci = 100
        self.dimensiune_strat_intrare = 4
        self.dimensiune_strat_ascuns = 4
        self.dimensiune_strat_iesire = 3
        self.w1 = np.random.randn(self.dimensiune_strat_intrare, self.dimensiune_strat_ascuns)
        self.w2 = np.random.randn(self.dimensiune_strat_ascuns, self.dimensiune_strat_iesire)

    def logistic_sigmoid(self, x):
        return (1 / (1 + np.exp(-x)))

    def sigmoid_derivate(self, x):
        return x(1 - x)

    def error_function(self, outputAsteptat, outputReal):
        return 0.5*((outputAsteptat - outputReal)**2)

    def forward_propagation(self, X):
        self.z2 = np.dot(X, self.w1)
        self.a2 = self.logistic_sigmoid(self.z2)
        self.z3 = np.dot(self.a2, self.w2)
        yHat = self.logistic_sigmoid(self.z3)
        return yHat

    def backward_propagation(self, X, y, yHat):
        delta3 = np.multiply(-(y - yHat), self.sigmoid_derivate(yHat))
        djdw2 = np.dot(self.a2.T, delta3)

        delta2 = np.dot(delta3, self.w2.T) * self.sigmoid_derivate(self.a2)
        djdw1 = np.dot(X.T, delta2)

        self.w1 = self.w1 - self.rata_invatare * djdw1
        self.w2 = self.w2 - self.rata_invatare * djdw2

    def train(self, X, y):
        for i in range(self.numar_maxim_epoci):
            yHat = self.forward_propagation(X)
            self.backward_propagation(X, y, yHat)

    def predict(self, X):
        yHat = self.forward_propagation(X)
        print("Predicted data based on trained weights: ")
        print("Input (scaled): \n" + str(X))
        print("Output: \n" + str(yHat))
        
    def evaluate(self, X, y):
        yHat = self.forward_propagation(X)
        print('Evaluating the trained neural network on unseen data: ')
        print("Input (scaled): \n" + str(X))
        print("Actual Output: \n" + str(y))
        print("Predicted Output: \n" + str(yHat))
        print("Loss: \n" + str(np.mean(np.square(y - yHat))))

    def check_convergence(self, X, y):
        yHat = self.forward_propagation(X)
        print("Loss: \n" + str(np.mean(np.square(y - yHat))))
        if np.mean(np.square(y - yHat)) < 0.1:
            return True
        return False


if __name__ == '__main__':
    Irisi = read_file()
    random.shuffle(Irisi)
    IrisiAntrenare = []
    IrisiTestare = []
    for i in range(0, int(len(Irisi) * 4 / 5)):
        IrisiAntrenare.append([Irisi[i].sepal_length, Irisi[i].sepal_width, Irisi[i].petal_length, Irisi[i].petal_width])
    for i in range(int(len(Irisi) * 4 / 5), len(Irisi)):
        IrisiTestare.append([Irisi[i].sepal_length, Irisi[i].sepal_width, Irisi[i].petal_length, Irisi[i].petal_width])
    print("Irisi pentru antrenare" + '-' * 50)
    for i in IrisiAntrenare:
        print(i)
    print("Irisi pentru testare" + '-' * 50)
    for i in IrisiTestare:
        print(i)

    nn = NeuralNetwork()
    fwd_prop_trg = nn.forward_propagation(IrisiAntrenare)
    fwd_prop_tst = nn.forward_propagation(IrisiTestare)
    nn.evaluate(IrisiTestare, fwd_prop_tst)
    nn.check_convergence(IrisiAntrenare, fwd_prop_trg)
REQ_UPLOADtest/Users/snistor/work/ai/lab6.pyINIT_SENDimport random
import numpy as np


class Iris:
    sepal_length = 0
    sepal_width = 0
    petal_length = 0
    petal_width = 0
    clasa = ''

    def __init__(self, sepal_length, sepal_width, petal_length, petal_width, clasa):
        self.sepal_length = float(sepal_length)
        self.sepal_width = float(sepal_width)
        self.petal_length = float(petal_length)
        self.petal_width = float(petal_width)
        self.clasa = clasa

    def __str__(self):
        return str(self.sepal_length) + ' ' + str(self.sepal_width) + ' ' + str(self.petal_length) + ' ' + str(
            self.petal_width) + ' ' + self.clasa


def read_file():
    f = open('iris.data')
    lista = []
    for line in f:
        line = line.strip()
        if line:
            lista.append(Iris(*line.split(',')))
    f.close()
    return lista


def convert_mat(mat):
    conv_mat = []
    for row in mat:
        conv_row = []
        for item in row.split(' '):
            try:
                conv_row.append(float(item))
            except ValueError as stupid_error:
                pass

        conv_mat.append(conv_row)
    return conv_mat


class NeuralNetwork:
    def __init__(self):
        self.rata_invatare = 0.1
        self.numar_maxim_epoci = 100
        self.dimensiune_strat_intrare = 4
        self.dimensiune_strat_ascuns = 4
        self.dimensiune_strat_iesire = 3
        self.w1 = np.random.randn(self.dimensiune_strat_intrare, self.dimensiune_strat_ascuns)
        self.w2 = np.random.randn(self.dimensiune_strat_ascuns, self.dimensiune_strat_iesire)

    def logistic_sigmoid(self, x):
        return (1 / (1 + np.exp(-x)))

    def sigmoid_derivate(self, x):
        return x(1 - x)

    def error_function(self, outputAsteptat, outputReal):
        return 0.5*((outputAsteptat - outputReal)**2)

    def forward_propagation(self, X):
        self.z2 = np.dot(X, self.w1)
        self.a2 = self.logistic_sigmoid(self.z2)
        self.z3 = np.dot(self.a2, self.w2)
        yHat = self.logistic_sigmoid(self.z3)
        return yHat

    def backward_propagation(self, X, y, yHat):
        delta3 = np.multiply(-(y - yHat), self.sigmoid_derivate(yHat))
        djdw2 = np.dot(self.a2.T, delta3)

        delta2 = np.dot(delta3, self.w2.T) * self.sigmoid_derivate(self.a2)
        djdw1 = np.dot(X.T, delta2)

        self.w1 = self.w1 - self.rata_invatare * djdw1
        self.w2 = self.w2 - self.rata_invatare * djdw2

    def train(self, X, y):
        for i in range(self.numar_maxim_epoci):
            yHat = self.forward_propagation(X)
            self.backward_propagation(X, y, yHat)

    def predict(self, X):
        yHat = self.forward_propagation(X)
        print("Predicted data based on trained weights: ")
        print("Input (scaled): \n" + str(X))
        print("Output: \n" + str(yHat))
        
    def evaluate(self, X, y):
        yHat = self.forward_propagation(X)
        print('Evaluating the trained neural network on unseen data: ')
        print("Input (scaled): \n" + str(X))
        print("Actual Output: \n" + str(y))
        print("Predicted Output: \n" + str(yHat))
        print("Loss: \n" + str(np.mean(np.square(y - yHat))))

    def check_convergence(self, X, y):
        yHat = self.forward_propagation(X)
        print("Loss: \n" + str(np.mean(np.square(y - yHat))))
        if np.mean(np.square(y - yHat)) < 0.1:
            return True
        return False


if __name__ == '__main__':
    Irisi = read_file()
    random.shuffle(Irisi)
    IrisiAntrenare = []
    IrisiTestare = []
    for i in range(0, int(len(Irisi) * 4 / 5)):
        IrisiAntrenare.append([Irisi[i].sepal_length, Irisi[i].sepal_width, Irisi[i].petal_length, Irisi[i].petal_width])
    for i in range(int(len(Irisi) * 4 / 5), len(Irisi)):
        IrisiTestare.append([Irisi[i].sepal_length, Irisi[i].sep
