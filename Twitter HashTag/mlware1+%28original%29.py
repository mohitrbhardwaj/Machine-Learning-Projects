
# coding: utf-8

# In[72]:

from sklearn import tree
from sklearn.model_selection import KFold
from sklearn import svm
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.model_selection import GridSearchCV
from sklearn.ensemble import BaggingRegressor
import matplotlib.pyplot as plt
from sklearn.preprocessing import Imputer
from sklearn.preprocessing import Imputer
from sklearn.metrics import r2_score
from sklearn.metrics import make_scorer
from sklearn import linear_model
from sklearn.preprocessing import Imputer
from sklearn.neighbors import KNeighborsClassifier
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from sklearn.naive_bayes import MultinomialNB
from sklearn.feature_extraction.text import CountVectorizer
# from sklearn

import pandas as pd
import numpy as np
import warnings
warnings.filterwarnings('ignore')
get_ipython().magic('pylab inline')


# In[73]:

clf=MultinomialNB()


# In[74]:

train_data = pd.read_csv('/home/mohitrbhardwaj/Desktop/kaggle/iit bhu mlware/mlware1/train_MLWARE1.csv')
test_data = pd.read_csv('/home/mohitrbhardwaj/Desktop/kaggle/iit bhu mlware/mlware1/test_MLWARE1.csv')


# In[75]:

count_vectorizer = CountVectorizer()
data1=numpy.asarray(train_data['tweet'])
concatenated_data=data1
counts = count_vectorizer.fit_transform(concatenated_data)
# counts = count_vectorizer.fit_transform(numpy.asarray(train_data['tweet'][80000:90000]))
# print(getnnz(counts))


# In[76]:

targets = numpy.asarray(train_data['label'])
# tar = numpy.asarray(train_data['label'][50000:90000])
# targets = numpy.concatenate((targets,tar),axis=0)
clf.fit(counts, targets)


# In[77]:

example_counts = count_vectorizer.transform(test_data['tweet'])
predictions = clf.predict(example_counts)
# print(clf.score(,numpy.asarray(train_data['label'])))


# In[79]:

sol = pd.DataFrame()
sol['ID']=test_data['ID']
sol['label']=predictions
sol.to_csv("submission.csv",index=False)


# In[ ]:



