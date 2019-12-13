typedef enum {
    r_newpg, r_deletepg, r_addob, r_deleteob, r_statpg, r_stampainv, r_cercainv, r_stamppg, r_err, r_fine
} comandi_e;

void selezionaDati(tabPg_t *tabPg, tabInv_t *tabInv, comandi_e codiceComando);
comandi_e leggiComando(void);