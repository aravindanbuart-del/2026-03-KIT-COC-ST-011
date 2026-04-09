import pandas as pd
df = pd.read_csv('merged_dataset.csv')
df.drop_duplicates(inplace=True)
df.dropna(inplace=True)
df['FinalGrade'] = 3 - df['FinalGrade']
print(df['FinalGrade'].value_counts())
import pandas as pd
df = pd.read_csv('merged_dataset.csv')
df.dropna(inplace=True)
df['FinalGrade'] = 3 - df['FinalGrade']
corr = df['ExamScore'].corr(df['FinalGrade'])
print(f"Correlation between ExamScore and FinalGrade: {corr:.4f}")

# Check unique values of FinalGrade
print(f"FinalGrade unique values: {df['FinalGrade'].unique()}")
# Check if FinalGrade is a direct mapping from ExamScore
# For example, 0-25: 0, 26-50: 1, etc.
import matplotlib.pyplot as plt
plt.scatter(df['ExamScore'], df['FinalGrade'])
plt.xlabel('ExamScore')import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder, StandardScaler, MinMaxScaler
from sklearn.cluster import KMeans
from sklearn.feature_selection import SelectKBest, f_classif

df = pd.read_csv('merged_dataset.csv')
df.drop_duplicates(inplace=True)
df.dropna(inplace=True)
le = LabelEncoder()
for col in df.select_dtypes(include=['object']).columns:
    df[col] = le.fit_transform(df[col])
df['FinalGrade'] = 3 - df['FinalGrade']

scaler_mm = MinMaxScaler()
norm_cols = ['Attendance', 'Discussions', 'AssignmentCompletion', 'Resources', 'OnlineCourses', 'StudyHours', 'Motivation', 'StressLevel']
df_norm = pd.DataFrame(scaler_mm.fit_transform(df[norm_cols]), columns=norm_cols, index=df.index)

df['Engagement_Index'] = (df_norm['Attendance'] * 0.4 + df_norm['Discussions'] * 0.3 + df_norm['AssignmentCompletion'] * 0.3)
df['Behavioural_Intensity'] = (df_norm['StudyHours'] * 0.5 + df_norm['Motivation'] * 0.5)

X_full = df.drop(['FinalGrade', 'ExamScore'], axis=1, errors='ignore')
y = df['FinalGrade']
selector = SelectKBest(f_classif, k=10)
selector.fit(X_full, y)
X = X_full[selector.get_feature_names_out()]

scaler_std = StandardScaler()
X_std = scaler_std.fit_transform(X)
kmeans = KMeans(n_clusters=4, random_state=42, n_init=10)
df['Cluster'] = kmeans.fit_predict(X_std)

print(f"Columns in df: {df.columns.tolist()}")
print(f"Engagement_Index in df? {'Engagement_Index' in df.columns}")

cluster_summary = df.groupby('Cluster').agg({
    'Engagement_Index': 'mean',
    'Behavioural_Intensity': 'mean',
    'FinalGrade': 'mean'
})
print("Agg complete")

plt.ylabel('FinalGrade')
plt.savefig('score_vs_grade.png')
import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder, StandardScaler, MinMaxScaler
from sklearn.cluster import KMeans
from sklearn.feature_selection import SelectKBest, f_classif

df = pd.read_csv('merged_dataset.csv')
df.drop_duplicates(inplace=True)
df.dropna(inplace=True)
le = LabelEncoder()
for col in df.select_dtypes(include=['object']).columns:
    df[col] = le.fit_transform(df[col])
df['FinalGrade'] = 3 - df['FinalGrade']

scaler_mm = MinMaxScaler()
norm_cols = ['Attendance', 'Discussions', 'AssignmentCompletion', 'Resources', 'OnlineCourses', 'StudyHours', 'Motivation', 'StressLevel']
df_norm = pd.DataFrame(scaler_mm.fit_transform(df[norm_cols]), columns=norm_cols, index=df.index)

df['Engagement_Index'] = (df_norm['Attendance'] * 0.4 + df_norm['Discussions'] * 0.3 + df_norm['AssignmentCompletion'] * 0.3)
df['Behavioural_Intensity'] = (df_norm['StudyHours'] * 0.5 + df_norm['Motivation'] * 0.5)

X_full = df.drop(['FinalGrade', 'ExamScore'], axis=1, errors='ignore')
y = df['FinalGrade']
selector = SelectKBest(f_classif, k=10)
selector.fit(X_full, y)
X = X_full[selector.get_feature_names_out()]

scaler_std = StandardScaler()
X_std = scaler_std.fit_transform(X)
kmeans = KMeans(n_clusters=4, random_state=42, n_init=10)
df['Cluster'] = kmeans.fit_predict(X_std)

print(f"Columns in df: {df.columns.tolist()}")
print(f"Engagement_Index in df? {'Engagement_Index' in df.columns}")

cluster_summary = df.groupby('Cluster').agg({
    'Engagement_Index': 'mean',
    'Behavioural_Intensity': 'mean',
    'FinalGrade': 'mean'
})
print("Agg complete")
