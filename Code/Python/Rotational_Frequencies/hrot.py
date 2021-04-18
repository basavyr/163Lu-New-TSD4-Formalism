#!/Users/robertpoenaru/.pyenv/versions/3.8.6/envs/scientific/bin/python

import numpy as np
import matplotlib.pyplot as plt

# Calculate the rotational frequencies for the band 4
E0 = 1.7399
renormalize = lambda x: [x[0], x[1] + E0]

exp_Data = [[23.5, 4.58], [25.5, 5.2251], [27.5, 5.9273], [29.5, 6.6819], [31.5, 7.4919], [
    33.5, 8.3573], [35.5, 9.2778], [37.5, 10.2535], [39.5, 11.2851], [41.5, 12.3701]]
th_Data = [[23.5, 4.32758], [25.5, 5.02986], [27.5, 5.78767], [29.5, 6.601], [31.5, 7.46986], [
    33.5, 8.39423], [35.5, 9.37413], [37.5, 10.4096], [39.5, 11.5005], [41.5, 12.647]]

exp_Data = list(map(renormalize, exp_Data))
th_Data = list(map(renormalize, th_Data))

# the rotational frequency ℎω
hrot_function = lambda e1, e2: 0.5 * (e1 - e2)


def Compute_Rotational_Frequencies(data_set):
    hrot_values = []
    for idx in range(1, len(data_set)):
        E_I = data_set[idx][1]
        E_IM2 = data_set[idx - 1][1]
        I = data_set[idx][0]
        hrot_values.append([I, hrot_function(E_I, E_IM2)])
    return hrot_values


for x in Compute_Rotational_Frequencies(exp_Data):
    pass
    # print(x)

# print(f'##############################')

for x in Compute_Rotational_Frequencies(th_Data):
    pass
    # print(x)


diffs_exp = []
diffs_th = []
delta_diffs = []
for idx in range(len(th_Data) - 1, 1, -1):
    delta_th = 0.5 * (th_Data[idx][1] - th_Data[idx - 1][1])
    delta_exp = 0.5 * (exp_Data[idx][1] - exp_Data[idx - 1][1])
    diffs_exp.append(delta_exp)
    diffs_th.append(delta_th)
    delta_diffs.append(abs(delta_th - delta_exp))


deltas = []
for idx in range(0, len(exp_Data)):
    deltas.append(abs(exp_Data[idx][1] - th_Data[idx][1]))

fig, ax = plt.subplots()

avg_diff = [(sum(delta_diffs) / len(delta_diffs))
            for _ in range(0, len(delta_diffs))]

diffs_th = [x - avg_diff[0] for x in diffs_th]

plt.plot(list(reversed(diffs_exp)), '-^r', label=r'$\delta_{I_1I_2};exp$')
plt.plot(list(reversed(diffs_th)), '-*k', label=r'$\delta_{I_1I_2};th$')
# plt.plot(delta_diffs, '-ob', label=r'$\delta_\delta$')
# plt.plot(avg_diff, '-ob', label=r'$\delta_\delta$')
ax.legend(loc='best')
plt.text(0.2, 0.8, f'avg_diff={np.round(avg_diff[0],2)}', horizontalalignment='center',
         verticalalignment='center', transform=ax.transAxes, fontsize=8)
ax.set_title(f'Rotational frequencies -> differential analysis')
ax.set_xlabel(r'$|I_{k} \rangle$')
ax.set_ylabel(r'$\delta$ [MeV]')
plt.savefig('diffs_exp.pdf', dpi=300, bbox_inches='tight')
plt.close()


print(avg_diff)

hrots_th = Compute_Rotational_Frequencies(th_Data)
hrots_exp = Compute_Rotational_Frequencies(exp_Data)
spins = [x[0] for x in hrots_exp]
hrots_exp = [x[1] for x in hrots_exp]
hrots_th = [x[1] - avg_diff[0] for x in hrots_th]


fig2, ax2 = plt.subplots()

plt.plot(spins, hrots_exp, '-^r', label=r'$\hbar\omega_{exp}$')
plt.plot(spins, hrots_th, '-*k', label=r'$\hbar\omega_{th}$')
plt.legend(loc='best')
ax2.set_title(f'Rotational frequencies -> differential analysis')
ax2.set_xlabel(r'I [$\hbar$]')
ax2.set_ylabel(r'$\hbar\omega$ [MeV]')
ax2.set_ylabel
plt.savefig('hrots.pdf', dpi=300, bbox_inches='tight')
plt.close()
