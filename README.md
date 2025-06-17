Aby działało należy włączyć venv następującymi komendami w terminalu:
python -m venv venv
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
.\venv\Scripts\Activate.ps1
pip install schedule

po zainstalowaniu tego trzeba po otwarciu vs code wpisać tylko:
.\venv\Scripts\Activate.ps1

I po tym śmiga z samym main:
python main.py

Zatrzymując program CTR+C pojawia się błąd, ale wynika on z tego, że program ma pętle, która sprawia, że cały czas działa i czeka na ustawioną godzinę, aby ponownie wysłać mail.

W config.json można zmieniać maila i godzinę wysłania.
